/*---------------------------------------------------------------------------*\
|                       _    _  _     ___                       | The         |
|     _____      ____ _| | _| || |   / __\__   __ _ _ __ ___    | Swiss       |
|    / __\ \ /\ / / _` | |/ / || |_ / _\/ _ \ / _` | '_ ` _ \   | Army        |
|    \__ \\ V  V / (_| |   <|__   _/ / | (_) | (_| | | | | | |  | Knife       |
|    |___/ \_/\_/ \__,_|_|\_\  |_| \/   \___/ \__,_|_| |_| |_|  | For         |
|                                                               | OpenFOAM    |
-------------------------------------------------------------------------------
License
    This file is part of swak4Foam.

    swak4Foam is free software; you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the
    Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    swak4Foam is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with swak4Foam; if not, write to the Free Software Foundation,
    Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Contributors/Copyright:
    2008-2011, 2013, 2015-2018 Bernhard F.W. Gschaider <bgschaid@hfd-research.com>

 SWAK Revision: $Id$
\*---------------------------------------------------------------------------*/

#include "initPotentialFlowFunctionObject.H"
#include "addToRunTimeSelectionTable.H"

#include "polyMesh.H"
#include "IOmanip.H"
#include "swakTime.H"

#include "fvMesh.H"
#include "volFields.H"
#include "surfaceInterpolate.H"
#include "fvmLaplacian.H"
#include "fvcDiv.H"
#include "fvcReconstruct.H"
#include "findRefCell.H"
#include "adjustPhi.H"

#include "swak.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{

    defineTypeNameAndDebug(initPotentialFlowFunctionObject, 0);

    addToRunTimeSelectionTable
    (
        functionObject,
        initPotentialFlowFunctionObject,
        dictionary
    );

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

initPotentialFlowFunctionObject::initPotentialFlowFunctionObject
(
    const word &name,
    const Time& t,
    const dictionary& dict
)
:
    updateSimpleFunctionObject(name,t,dict)
{
#ifdef FOAM_FUNCTIONOBJECT_HAS_SEPARATE_WRITE_METHOD_AND_NO_START
    start();
#endif
}

bool initPotentialFlowFunctionObject::start()
{
    UName_=word(dict_.lookup("UName"));
    pName_=word(dict_.lookup("pName"));
    writeOldFields_=readBool(dict_.lookup("writeOldFields"));
    writeFields_=readBool(dict_.lookup("writeFields"));
    overrideP_=readBool(dict_.lookup("overrideP"));
    initialiseUBCs_=readBool(dict_.lookup("initialiseUBCs"));

    return updateSimpleFunctionObject::start();
}

void initPotentialFlowFunctionObject::recalc()
{
    Info << "Solving potential flow for velocity " << UName_
        << " and pressure " << pName_ << endl;
    Pbug << "Starting recalc()" << endl;

    const fvMesh &mesh=dynamicCast<const fvMesh>(obr_);

    const dictionary& potentialFlow =
        mesh
#ifdef FOAM_FVMESH_HAS_NO_SOLUTIONDICT_METHOD
        .solution().dict()
#else
        .solutionDict()
#endif
        .subDict("potentialFlow");

    const int nNonOrthCorr =
        potentialFlow.lookupOrDefault<int>("nNonOrthogonalCorrectors", 0);

    volScalarField p(
        pName_+"Potential",
        mesh.lookupObject<volScalarField>(pName_)
    );
#ifdef FOAM_FVSCHEMES_HAS_SETFLUXREQUIRED
    mesh.schemesDict().setFluxRequired(p.name());
#endif
    volVectorField &U=const_cast<volVectorField&>(
        mesh.lookupObject<volVectorField>(UName_)
    );
    if(writeOldFields_) {
        Info << "Writing copy of old " << UName_ << endl;
        volVectorField oldU(UName_+".prepotential",U);
        oldU.write();
    }
    surfaceScalarField phi
    (
        IOobject
        (
            "phiPotential",
            mesh.time().timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::NO_WRITE
        ),
        fvc::interpolate(U) & mesh.Sf()
    );

    if(initialiseUBCs_) {
        U.correctBoundaryConditions();
        phi = fvc::interpolate(U) & mesh.Sf();
    }

    label pRefCell = 0;
    scalar pRefValue = 0.0;
    setRefCell
    (
        p,
        potentialFlow,
        pRefCell,
        pRefValue
    );

    adjustPhi(phi, U, p);

    //    fvOptions.relativeFlux(phi);

    for (int nonOrth=0; nonOrth<=nNonOrthCorr; nonOrth++)
    {
        Pbug << "Solve nonOrth " << nonOrth << endl;

        fvScalarMatrix pEqn
        (
            fvm::laplacian
            (
                dimensionedScalar
                (
                    "1",
                    dimTime/p.dimensions()*dimensionSet(0, 2, -2, 0, 0),
                    1
                ),
                p
            )
         ==
            fvc::div(phi)
        );

        pEqn.setReference(pRefCell, pRefValue);

#ifdef FOAM_FV_MESH_HAS_NO_SOLVERDICT
        pEqn.solve(mesh.solutionDict().subDict(pName_+".potential"));
#else
        pEqn.solve(
            mesh
#ifdef FOAM_FVMESH_HAS_NO_SOLUTIONDICT_METHOD
            .solution()
#endif
            .solverDict(pName_+".potential")
        );
#endif

        if (nonOrth == nNonOrthCorr)
        {
            phi -= pEqn.flux();
        }
    }

    //    fvOptions.absoluteFlux(phi);

    Info<< "continuity error = "
        << mag(fvc::div(phi))().weightedAverage(mesh.V()).value()
        << endl;

    U = fvc::reconstruct(phi);
    U.correctBoundaryConditions();

    Info<< "Interpolated U error = "
        << (sqrt(sum(sqr((fvc::interpolate(U) & mesh.Sf()) - phi)))
          /sum(mesh.magSf())).value()
        << endl;

    if(writeFields_) {
        Info << "Writing new value of " << UName_ << endl;
        U.write();
    }

    if(overrideP_) {
        if(writeOldFields_) {
            Info << "Writing old value of " << pName_ << endl;
            volScalarField pOld(
                pName_+".prepotential",
                mesh.lookupObject<volScalarField>(pName_)
            );
            pOld.write();
        }
        Info << "Overriding value of " << pName_ << endl;
        volScalarField &pNew=const_cast<volScalarField &>(
            mesh.lookupObject<volScalarField>(pName_)
        );
        pNew==p;
        if(writeFields_) {
            Info << "Writing new value of " << pName_ << endl;
            pNew.write();
        }
    }
    Pbug << "Ended recalc()" << endl;
}

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

} // namespace Foam

// ************************************************************************* //
