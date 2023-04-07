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
    Foam::bloodPlasmaTransport

Group
    grpSpecieTransport

Description
    Constant properties Transport package.
    Templated into a given thermodynamics package (needed for thermal
    conductivity).

SourceFiles
    bloodPlasmaTransportI.H
    bloodPlasmaTransport.C

\*---------------------------------------------------------------------------*/

#ifndef bloodPlasmaTransport_H
#define bloodPlasmaTransport_H

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// Forward Declarations

template <class Thermo> class bloodPlasmaTransport;

template <class Thermo>
inline bloodPlasmaTransport<Thermo> operator+(const bloodPlasmaTransport<Thermo> &, const bloodPlasmaTransport<Thermo> &);

template <class Thermo> inline bloodPlasmaTransport<Thermo> operator*(const scalar, const bloodPlasmaTransport<Thermo> &);

template <class Thermo> Ostream &operator<<(Ostream &, const bloodPlasmaTransport<Thermo> &);

/*---------------------------------------------------------------------------*\
                           Class bloodPlasmaTransport Declaration
\*---------------------------------------------------------------------------*/

template <class Thermo> class bloodPlasmaTransport : public Thermo
{
    // Private Data

    //- Constant dynamic viscosity [Pa.s]
    scalar mu_;

    //- Reciprocal Prandtl Number [-]
    scalar rPr_;

    // Private Member Functions

    //- Construct from components
    inline bloodPlasmaTransport(const Thermo &t, const scalar mu, const scalar Pr);

  public:
    // Generated Methods: copy construct, copy assignment

    // Constructors

    //- Construct as named copy
    inline bloodPlasmaTransport(const word &, const bloodPlasmaTransport &);

    //- Construct from dictionary
    explicit bloodPlasmaTransport(const dictionary &dict);

    //- Construct and return a clone
    inline autoPtr<bloodPlasmaTransport> clone() const;

    // Selector from dictionary
    inline static autoPtr<bloodPlasmaTransport> New(const dictionary &dict);

    // Member Functions

    //- Return the instantiated type name
    static word typeName()
    {
        return "bloodPlasma<" + Thermo::typeName() + '>';
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

    inline void operator+=(const bloodPlasmaTransport &);

    inline void operator*=(const scalar);

    // Friend Operators

    friend bloodPlasmaTransport operator+<Thermo>(const bloodPlasmaTransport &, const bloodPlasmaTransport &);

    friend bloodPlasmaTransport operator*<Thermo>(const scalar, const bloodPlasmaTransport &);

    // IOstream Operators

    friend Ostream &operator<< <Thermo>(Ostream &, const bloodPlasmaTransport &);
};

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "bloodPlasmaTransportI.H"

#ifdef NoRepository
#include "bloodPlasmaTransport.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
