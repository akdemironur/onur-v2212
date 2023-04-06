/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2017 OpenFOAM Foundation
    Copyright (C) 2020-2021 OpenCFD Ltd.
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

#include "bloodrhoThermo.H"
#include "makeThermo.H"

/* #include "Boussinesq.H" */
/* #include "PengRobinsonGas.H" */
/* #include "adiabaticPerfectFluid.H" */
/* #include "icoTabulated.H" */
/* #include "incompressiblePerfectGas.H" */
#include "perfectFluid.H"
#include "perfectGas.H"
/* #include "rPolynomial.H" */
/* #include "rhoConst.H" */
#include "specie.H"

#include "eConstThermo.H"
#include "hConstThermo.H"
/* #include "hTabulatedThermo.H" */
/* #include "janafThermo.H" */
#include "sensibleEnthalpy.H"
#include "sensibleInternalEnergy.H"
#include "thermo.H"

/* #include "constTransport.H" */
/* #include "sutherlandTransport.H" */
/* #include "WLFTransport.H" */
#include "bloodTransport.H"
/* #include "icoPolynomial.H" */
/* #include "hPolynomialThermo.H" */
/* #include "polynomialTransport.H" */
/* #include "tabulatedTransport.H" */

#include "bloodheRhoThermo.H"
#include "pureMixture.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam {

/* * * * * * * * * * * * * * * Private Static Data * * * * * * * * * * * * * */

makeThermos(bloodrhoThermo, bloodheRhoThermo, pureMixture, bloodTransport,
            sensibleEnthalpy, hConstThermo, perfectGas, specie);
makeThermos(bloodrhoThermo, bloodheRhoThermo, pureMixture, bloodTransport,
            sensibleEnthalpy, hConstThermo, perfectFluid, specie);
makeThermos(bloodrhoThermo, bloodheRhoThermo, pureMixture, bloodTransport,
            sensibleInternalEnergy, eConstThermo, perfectGas, specie);
makeThermos(bloodrhoThermo, bloodheRhoThermo, pureMixture, bloodTransport,
            sensibleInternalEnergy, eConstThermo, perfectFluid, specie);

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// ************************************************************************* //
