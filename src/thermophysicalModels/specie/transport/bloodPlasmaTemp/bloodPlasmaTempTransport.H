/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2017 OpenFOAM Foundation
    Copyright (C) 2020 OpenCFD Ltd.
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

Class
    Foam::bloodPlasmaTempTransport

Group
    grpSpecieTransport

Description
    Constant properties Transport package.
    Templated into a given thermodynamics package (needed for thermal
    conductivity).

SourceFiles
    bloodPlasmaTempTransportI.H
    bloodPlasmaTempTransport.C

\*---------------------------------------------------------------------------*/

#ifndef bloodPlasmaTempTransport_H
#define bloodPlasmaTempTransport_H

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// Forward Declarations

template <class Thermo> class bloodPlasmaTempTransport;

template <class Thermo>
inline bloodPlasmaTempTransport<Thermo> operator+(const bloodPlasmaTempTransport<Thermo> &, const bloodPlasmaTempTransport<Thermo> &);

template <class Thermo> inline bloodPlasmaTempTransport<Thermo> operator*(const scalar, const bloodPlasmaTempTransport<Thermo> &);

template <class Thermo> Ostream &operator<<(Ostream &, const bloodPlasmaTempTransport<Thermo> &);

/*---------------------------------------------------------------------------*\
                           Class bloodPlasmaTempTransport Declaration
\*---------------------------------------------------------------------------*/

template <class Thermo> class bloodPlasmaTempTransport : public Thermo
{
    // Private Data

    //- Constant dynamic viscosity [Pa.s]
    scalar mu_;

    //- Reciprocal Prandtl Number [-]
    scalar rPr_;

    // Private Member Functions

    //- Construct from components
    inline bloodPlasmaTempTransport(const Thermo &t, const scalar mu, const scalar Pr);

  public:
    // Generated Methods: copy construct, copy assignment

    // Constructors

    //- Construct as named copy
    inline bloodPlasmaTempTransport(const word &, const bloodPlasmaTempTransport &);

    //- Construct from dictionary
    explicit bloodPlasmaTempTransport(const dictionary &dict);

    //- Construct and return a clone
    inline autoPtr<bloodPlasmaTempTransport> clone() const;

    // Selector from dictionary
    inline static autoPtr<bloodPlasmaTempTransport> New(const dictionary &dict);

    // Member Functions

    //- Return the instantiated type name
    static word typeName()
    {
        return "bloodPlasmaTemp<" + Thermo::typeName() + '>';
    }

    //- Dynamic viscosity [kg/ms]
    inline scalar mu(const scalar p, const scalar T, const scalar sr, const scalar alphaplasma) const;

    //- Thermal conductivity [W/mK]
    inline scalar kappa(const scalar p, const scalar T, const scalar sr, const scalar alphaplasma) const;

    //- Thermal diffusivity of enthalpy [kg/ms]
    inline scalar alphah(const scalar p, const scalar T, const scalar sr, const scalar alphaplasma) const;

    // Species diffusivity
    // inline scalar D(const scalar p, const scalar T) const;

    //- Write to Ostream
    void write(Ostream &os) const;

    // Member Operators

    inline void operator+=(const bloodPlasmaTempTransport &);

    inline void operator*=(const scalar);

    // Friend Operators

    friend bloodPlasmaTempTransport operator+<Thermo>(const bloodPlasmaTempTransport &, const bloodPlasmaTempTransport &);

    friend bloodPlasmaTempTransport operator*<Thermo>(const scalar, const bloodPlasmaTempTransport &);

    // IOstream Operators

    friend Ostream &operator<< <Thermo>(Ostream &, const bloodPlasmaTempTransport &);
};

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "bloodPlasmaTempTransportI.H"

#ifdef NoRepository
#include "bloodPlasmaTempTransport.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
