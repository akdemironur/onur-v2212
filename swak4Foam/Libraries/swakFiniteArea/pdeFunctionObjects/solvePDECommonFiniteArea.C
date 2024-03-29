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
    2011, 2013, 2016-2018 Bernhard F.W. Gschaider <bgschaid@hfd-research.com>

 SWAK Revision: $Id:  $
\*---------------------------------------------------------------------------*/

#include "solvePDECommonFiniteArea.H"

#include "polyMesh.H"

#include "areaFields.H"

#include "FaFieldValueExpressionDriver.H"

#include "faScalarMatrix.H"

#include "fvm.H"

namespace Foam {
    defineTypeNameAndDebug(solvePDECommonFiniteArea,0);
}

Foam::solvePDECommonFiniteArea::solvePDECommonFiniteArea
(
    const word& name,
    const objectRegistry& obr,
    const dictionary& dict,
    const bool loadFromFiles
):
    solvePDECommon(
        name,
        obr,
        dict,
        loadFromFiles
    )
{
    Dbug << " Constructor" << endl;

    if (!isA<polyMesh>(obr))
    {
        active_=false;
        WarningIn("solvePDECommonFiniteArea::solvePDECommonFiniteArea")
            << "Not a polyMesh. Nothing I can do"
                << endl;
    }
}

Foam::solvePDECommonFiniteArea::~solvePDECommonFiniteArea()
{}

Foam::areaScalarField &Foam::solvePDECommonFiniteArea::theField()
{
    // either the field was created by someone else ... then it should be
    // in the registry. Or we created it.
    if(theField_.valid()) {
        Dbug << fieldName_ << " theField is owned" << endl;
        return theField_();
    } else {
        Dbug << fieldName_ << " theField is not owned" << endl;
        return const_cast<areaScalarField&>(
            obr_.lookupObject<areaScalarField>(
                fieldName_
            )
        );
    }
}

void Foam::solvePDECommonFiniteArea::read(const dictionary& dict)
{
    Dbug << " - read" << endl;

    solvePDECommon::read(dict);

    Dbug << " - read - after common" << endl;

    if(active_) {
        const fvMesh& mesh = refCast<const fvMesh>(obr_);

        if(
            theField_.valid()
            &&
            fieldName_!=theField_->name()
        ) {
            WarningIn("Foam::solvePDECommonFiniteArea::read(const dictionary& dict)")
                << "Throwing out field " << theField_->name()
                    << " and loading " << fieldName_ << ". "
                    << "This might lead to unpredicatable behaviour" << endl;
            theField_.clear();
        }

        driver_.reset(
            new FaFieldValueExpressionDriver(
                mesh,
                false, // no caching. No need
                true,  // search fields in memory
                false  // don't look up files on disc
            )
        );

        if(!theField_.valid()) {
            Dbug << " ::read - no valid field" << endl;

            if(obr_.foundObject<areaScalarField>(fieldName_)) {
                Dbug << " ::read " << fieldName_ << " in memory" << endl;
                if(!dict.found("useFieldFromMemory")) {
                    FatalErrorIn("Foam::solvePDECommonFiniteArea::read(const dictionary& dict)")
                        << "Field " << fieldName_ << " alread in memory. "
                            << "Set 'useFieldFromMemory true;' to use it or "
                            << "use different name"
                            << endl
                            << exit(FatalError);
                }
                bool useFieldFromMemory=readBool(
                    dict.lookup("useFieldFromMemory")
                );
                if(!useFieldFromMemory) {
                    FatalErrorIn("Foam::solvePDECommonFiniteArea::read(const dictionary& dict)")
                        << "Field " << fieldName_ << " alread in memory. "
                            << "Use different name"
                            << endl
                            << exit(FatalError);
                }
            } else {
                Dbug << " ::read " << fieldName_ << " reading from disk at "
                    << mesh.time().timeName() << endl;
                theField_.reset(
                    new areaScalarField(
                        IOobject (
                            fieldName_,
                            mesh.time().timeName(),
                            mesh,
                            IOobject::MUST_READ,
                            IOobject::AUTO_WRITE
                        ),
                        driver_->aMesh()
                    )
                );
            }
        }

        driver_->readVariablesAndTables(dict);

        driver_->createWriterAndRead(name_+"_"+fieldName_+"_"+type());
    }
}

void Foam::solvePDECommonFiniteArea::writeData()
{
    theField_->write();

    driver_->tryWrite();
}

void Foam::solvePDECommonFiniteArea::writeNewField()
{
    theField().write();
}

void Foam::solvePDECommonFiniteArea::writeOldField()
{
    areaScalarField temp(fieldName_+".presolve",theField());
    temp.write();
}

// ************************************************************************* //
