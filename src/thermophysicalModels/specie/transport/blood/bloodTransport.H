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
    Foam::bloodTransport

Group
    grpSpecieTransport

Description
    Constant properties Transport package.
    Templated into a given thermodynamics package (needed for thermal
    conductivity).

SourceFiles
    bloodTransportI.H
    bloodTransport.C

\*---------------------------------------------------------------------------*/

#ifndef bloodTransport_H
#define bloodTransport_H

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// Forward Declarations

template<class Thermo> class bloodTransport;

template<class Thermo>
inline bloodTransport<Thermo> operator+
(
    const bloodTransport<Thermo>&,
    const bloodTransport<Thermo>&
);

template<class Thermo>
inline bloodTransport<Thermo> operator*
(
    const scalar,
    const bloodTransport<Thermo>&
);

template<class Thermo>
Ostream& operator<<
(
    Ostream&,
    const bloodTransport<Thermo>&
);


/*---------------------------------------------------------------------------*\
                           Class bloodTransport Declaration
\*---------------------------------------------------------------------------*/

template<class Thermo>
class bloodTransport
:
    public Thermo
{
    // Private Data

        //- Constant dynamic viscosity [Pa.s]
        scalar mu_;

        //- Reciprocal Prandtl Number [-]
        scalar rPr_;


    // Private Member Functions

        //- Construct from components
        inline bloodTransport
        (
            const Thermo& t,
            const scalar mu,
            const scalar Pr
        );


public:

    // Generated Methods: copy construct, copy assignment


    // Constructors

        //- Construct as named copy
        inline bloodTransport(const word&, const bloodTransport&);

        //- Construct from dictionary
        explicit bloodTransport(const dictionary& dict);

        //- Construct and return a clone
        inline autoPtr<bloodTransport> clone() const;

        // Selector from dictionary
        inline static autoPtr<bloodTransport> New(const dictionary& dict);


    // Member Functions

        //- Return the instantiated type name
        static word typeName()
        {
            return "blood<" + Thermo::typeName() + '>';
        }

        //- Dynamic viscosity [kg/ms]
        inline scalar mu(const scalar p, const scalar T) const;

        //- Thermal conductivity [W/mK]
        inline scalar kappa(const scalar p, const scalar T) const;

        //- Thermal diffusivity of enthalpy [kg/ms]
        inline scalar alphah(const scalar p, const scalar T) const;

        // Species diffusivity
        //inline scalar D(const scalar p, const scalar T) const;

        //- Write to Ostream
        void write(Ostream& os) const;


    // Member Operators

        inline void operator+=(const bloodTransport&);

        inline void operator*=(const scalar);


    // Friend Operators

        friend bloodTransport operator+ <Thermo>
        (
            const bloodTransport&,
            const bloodTransport&
        );

        friend bloodTransport operator* <Thermo>
        (
            const scalar,
            const bloodTransport&
        );


    // IOstream Operators

        friend Ostream& operator<< <Thermo>
        (
            Ostream&,
            const bloodTransport&
        );
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "bloodTransportI.H"

#ifdef NoRepository
    #include "bloodTransport.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
