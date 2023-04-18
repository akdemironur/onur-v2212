/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2017 OpenFOAM Foundation
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

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template <class Thermo>
inline Foam::bloodPlasmaTempTransport<Thermo>::bloodPlasmaTempTransport(const Thermo &t, const scalar mu,
                                                                        const scalar Pr)
    : Thermo(t), mu_(mu), rPr_(1.0 / Pr)
{
}

template <class Thermo>
inline Foam::bloodPlasmaTempTransport<Thermo>::bloodPlasmaTempTransport(const word &name,
                                                                        const bloodPlasmaTempTransport &ct)
    : Thermo(name, ct), mu_(ct.mu_), rPr_(ct.rPr_)
{
}

template <class Thermo>
inline Foam::autoPtr<Foam::bloodPlasmaTempTransport<Thermo>> Foam::bloodPlasmaTempTransport<Thermo>::clone() const
{
    return autoPtr<bloodPlasmaTempTransport<Thermo>>::New(*this);
}

template <class Thermo>
inline Foam::autoPtr<Foam::bloodPlasmaTempTransport<Thermo>> Foam::bloodPlasmaTempTransport<Thermo>::New(
    const dictionary &dict)
{
    return autoPtr<bloodPlasmaTempTransport<Thermo>>::New(dict);
}

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template <class Thermo>
inline Foam::scalar Foam::bloodPlasmaTempTransport<Thermo>::mu(const scalar p, const scalar T, const scalar sr,
                                                               const scalar alphaplasma) const
{
    scalar muplasma;
    muplasma = scalar(-3.13272070e-08) * T * T * T + scalar(2.89621002e-05) * T * T + scalar(-8.95638907e-03) * T +
               scalar(9.27671328e-01);

    return muplasma;
}

template <class Thermo>
inline Foam::scalar Foam::bloodPlasmaTempTransport<Thermo>::kappa(const scalar p, const scalar T, const scalar sr,
                                                                  const scalar alphaplasma) const
{
    return this->Cp(p, T) * mu(p, T, sr, alphaplasma) * rPr_;
}

template <class Thermo>
inline Foam::scalar Foam::bloodPlasmaTempTransport<Thermo>::alphah(const scalar p, const scalar T, const scalar sr,
                                                                   const scalar alphaplasma) const
{
    return mu(p, T, sr, alphaplasma) * rPr_;
}

// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template <class Thermo>
inline void Foam::bloodPlasmaTempTransport<Thermo>::operator+=(const bloodPlasmaTempTransport<Thermo> &st)
{
    scalar Y1 = this->Y();

    Thermo::operator+=(st);

    if (mag(this->Y()) > SMALL)
    {
        Y1 /= this->Y();
        scalar Y2 = st.Y() / this->Y();

        mu_ = Y1 * mu_ + Y2 * st.mu_;
        rPr_ = 1.0 / (Y1 / rPr_ + Y2 / st.rPr_);
    }
}

template <class Thermo> inline void Foam::bloodPlasmaTempTransport<Thermo>::operator*=(const scalar s)
{
    Thermo::operator*=(s);
}

// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

template <class Thermo>
inline Foam::bloodPlasmaTempTransport<Thermo> Foam::operator+(const bloodPlasmaTempTransport<Thermo> &ct1,
                                                              const bloodPlasmaTempTransport<Thermo> &ct2)
{
    Thermo t(static_cast<const Thermo &>(ct1) + static_cast<const Thermo &>(ct2));

    if (mag(t.Y()) < SMALL)
    {
        return bloodPlasmaTempTransport<Thermo>(t, 0, ct1.rPr_);
    }
    else
    {
        scalar Y1 = ct1.Y() / t.Y();
        scalar Y2 = ct2.Y() / t.Y();

        return bloodPlasmaTempTransport<Thermo>(t, Y1 * ct1.mu_ + Y2 * ct2.mu_, 1.0 / (Y1 / ct1.rPr_ + Y2 / ct2.rPr_));
    }
}

template <class Thermo>
inline Foam::bloodPlasmaTempTransport<Thermo> Foam::operator*(const scalar s,
                                                              const bloodPlasmaTempTransport<Thermo> &ct)
{
    return bloodPlasmaTempTransport<Thermo>(s * static_cast<const Thermo &>(ct), ct.mu_, 1.0 / ct.rPr_);
}

// ************************************************************************* //
