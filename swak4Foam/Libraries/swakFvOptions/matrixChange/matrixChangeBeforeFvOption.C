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

    swak4Foam is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    swak4Foam is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with swak4Foam.  If not, see <http://www.gnu.org/licenses/>.

Contributors/Copyright:
    2017-2018 Bernhard F.W. Gschaider <bgschaid@hfd-research.com>

 SWAK Revision: $Id$
\*---------------------------------------------------------------------------*/

#include "swak.H"

#ifdef FOAM_FVOPTIONS_IS_NOW_FVMODELS
#warning "matrixChangeBefore not ported for this OF version"
#else

#include "matrixChangeBeforeFvOption.H"
#include "fvMatrices.H"
#include "DimensionedField.H"
#include "IFstream.H"
#include "addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * Static Member Functions * * * * * * * * * * * * //

namespace Foam
{
namespace fv
{
    defineTypeNameAndDebug(matrixChangeBeforeFvOption, 0);

    addToRunTimeSelectionTable
    (
        option,
        matrixChangeBeforeFvOption,
        dictionary
    );
}
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //



// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::fv::matrixChangeBeforeFvOption::matrixChangeBeforeFvOption
(
    const word& sourceName,
    const word& modelType,
    const dictionary& dict,
    const fvMesh& mesh
)
:
    matrixChangeBaseFvOption(sourceName, modelType, dict, mesh)
{
}

Foam::fv::matrixChangeBeforeFvOption::~matrixChangeBeforeFvOption()
{
}

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class T>
void Foam::fv::matrixChangeBeforeFvOption::setResidual(
    const fvMatrix<T>& matrix,
    autoPtr<GeometricField<T,fvPatchField,volMesh> >& val
) {
    Info << this->name() << " setting residual for "
        << matrix.psi().name() << " to " << this->fieldName() << endl;

    if(!val.valid()) {
        val.reset(
            new GeometricField<T,fvPatchField,volMesh>(
                IOobject(
                    this->fieldName(),
                    matrix.psi().mesh().time().timeName(),
                    matrix.psi().mesh(),
                    IOobject::NO_READ,
                    IOobject::AUTO_WRITE
                ),
                matrix.psi().mesh(),
                dimensioned<T>(
                    "no",
                    matrix.dimensions()/dimVolume,
                    pTraits<T>::zero
                )
            )
        );
    }
    val()=this->calcResiduum(matrix);
}

void Foam::fv::matrixChangeBeforeFvOption::addSup
(
    fvMatrix<vector>& eqn,
    const label fieldI
)
{
    if(doAtAddSup()) {
        setResidual(eqn,vectorResidual_);
    }
}

#ifdef FOAM_FVOPTION_HAS_ADDITIONAL_ADDSUP
void Foam::fv::matrixChangeBeforeFvOption::addSup
(
    const volScalarField& rho,
    fvMatrix<vector>& eqn,
    const label fieldI
)
{
    if(doAtAddSup()) {
        setResidual(eqn,vectorResidual_);
    }
}

void Foam::fv::matrixChangeBeforeFvOption::addSup
(
    const volScalarField& alpha,
    const volScalarField& rho,
    fvMatrix<vector>& eqn,
    const label fieldI
)
{
    if(doAtAddSup()) {
        setResidual(eqn,vectorResidual_);
    }
}
#endif


void Foam::fv::matrixChangeBeforeFvOption::addSup
(
    fvMatrix<scalar>& eqn,
    const label fieldI
)
{
    if(doAtAddSup()) {
        setResidual(eqn,scalarResidual_);
    }
}

#ifdef FOAM_FVOPTION_HAS_ADDITIONAL_ADDSUP
void Foam::fv::matrixChangeBeforeFvOption::addSup
(
    const volScalarField& rho,
    fvMatrix<scalar>& eqn,
    const label fieldI
)
{
    if(doAtAddSup()) {
        setResidual(eqn,scalarResidual_);
    }
}

void Foam::fv::matrixChangeBeforeFvOption::addSup
(
    const volScalarField& alpha,
    const volScalarField& rho,
    fvMatrix<scalar>& eqn,
    const label fieldI
)
{
    if(doAtAddSup()) {
        setResidual(eqn,scalarResidual_);
    }
}
#endif


void Foam::fv::matrixChangeBeforeFvOption::addSup
(
    fvMatrix<tensor>& eqn,
    const label fieldI
)
{
    if(doAtAddSup()) {
        setResidual(eqn,tensorResidual_);
    }
}

#ifdef FOAM_FVOPTION_HAS_ADDITIONAL_ADDSUP
void Foam::fv::matrixChangeBeforeFvOption::addSup
(
    const volScalarField& rho,
    fvMatrix<tensor>& eqn,
    const label fieldI
)
{
    if(doAtAddSup()) {
        setResidual(eqn,tensorResidual_);
    }
}

void Foam::fv::matrixChangeBeforeFvOption::addSup
(
    const volScalarField& alpha,
    const volScalarField& rho,
    fvMatrix<tensor>& eqn,
    const label fieldI
)
{
    if(doAtAddSup()) {
        setResidual(eqn,tensorResidual_);
    }
}
#endif


void Foam::fv::matrixChangeBeforeFvOption::addSup
(
    fvMatrix<symmTensor>& eqn,
    const label fieldI
)
{
    if(doAtAddSup()) {
        setResidual(eqn,symmTensorResidual_);
    }
}

#ifdef FOAM_FVOPTION_HAS_ADDITIONAL_ADDSUP
void Foam::fv::matrixChangeBeforeFvOption::addSup
(
    const volScalarField& rho,
    fvMatrix<symmTensor>& eqn,
    const label fieldI
)
{
    if(doAtAddSup()) {
        setResidual(eqn,symmTensorResidual_);
    }
}

void Foam::fv::matrixChangeBeforeFvOption::addSup
(
    const volScalarField& alpha,
    const volScalarField& rho,
    fvMatrix<symmTensor>& eqn,
    const label fieldI
)
{
    if(doAtAddSup()) {
        setResidual(eqn,symmTensorResidual_);
    }
}
#endif


void Foam::fv::matrixChangeBeforeFvOption::addSup
(
    fvMatrix<sphericalTensor>& eqn,
    const label fieldI
)
{
    if(doAtAddSup()) {
        setResidual(eqn,sphericalTensorResidual_);
    }
}

#ifdef FOAM_FVOPTION_HAS_ADDITIONAL_ADDSUP
void Foam::fv::matrixChangeBeforeFvOption::addSup
(
    const volScalarField& rho,
    fvMatrix<sphericalTensor>& eqn,
    const label fieldI
)
{
    if(doAtAddSup()) {
        setResidual(eqn,sphericalTensorResidual_);
    }
}

void Foam::fv::matrixChangeBeforeFvOption::addSup
(
    const volScalarField& alpha,
    const volScalarField& rho,
    fvMatrix<sphericalTensor>& eqn,
    const label fieldI
)
{
    if(doAtAddSup()) {
        setResidual(eqn,sphericalTensorResidual_);
    }
}
#endif

void Foam::fv::matrixChangeBeforeFvOption::setValue
(
    fvMatrix<vector>& eqn,
    const label fieldI
)
{
    if(!doAtAddSup()) {
        setResidual(eqn,vectorResidual_);
    }
}



void Foam::fv::matrixChangeBeforeFvOption::setValue
(
    fvMatrix<scalar>& eqn,
    const label fieldI
)
{
    if(!doAtAddSup()) {
        setResidual(eqn,scalarResidual_);
    }
}


void Foam::fv::matrixChangeBeforeFvOption::setValue
(
    fvMatrix<tensor>& eqn,
    const label fieldI
)
{
    if(!doAtAddSup()) {
        setResidual(eqn,tensorResidual_);
    }
}


void Foam::fv::matrixChangeBeforeFvOption::setValue
(
    fvMatrix<symmTensor>& eqn,
    const label fieldI
)
{
    if(!doAtAddSup()) {
        setResidual(eqn,symmTensorResidual_);
    }
}


void Foam::fv::matrixChangeBeforeFvOption::setValue
(
    fvMatrix<sphericalTensor>& eqn,
    const label fieldI
)
{
    if(!doAtAddSup()) {
        setResidual(eqn,sphericalTensorResidual_);
    }
}

#endif

// ************************************************************************* //
