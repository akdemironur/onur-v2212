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
inline Foam::bloodRBCTempTransport<Thermo>::bloodRBCTempTransport(const Thermo &t, const scalar mu, const scalar Pr)
    : Thermo(t), mu_(mu), rPr_(1.0 / Pr)
{
}

template <class Thermo>
inline Foam::bloodRBCTempTransport<Thermo>::bloodRBCTempTransport(const word &name, const bloodRBCTempTransport &ct)
    : Thermo(name, ct), mu_(ct.mu_), rPr_(ct.rPr_)
{
}

template <class Thermo>
inline Foam::autoPtr<Foam::bloodRBCTempTransport<Thermo>> Foam::bloodRBCTempTransport<Thermo>::clone() const
{
    return autoPtr<bloodRBCTempTransport<Thermo>>::New(*this);
}

template <class Thermo>
inline Foam::autoPtr<Foam::bloodRBCTempTransport<Thermo>> Foam::bloodRBCTempTransport<Thermo>::New(
    const dictionary &dict)
{
    return autoPtr<bloodRBCTempTransport<Thermo>>::New(dict);
}

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template <class Thermo>
inline Foam::scalar Foam::bloodRBCTempTransport<Thermo>::mu(const scalar p, const scalar T, const scalar sr,
                                                            const scalar alphaplasma) const
{
    scalar alphaRBC = scalar(1) - alphaplasma;
    scalar lambda = scalar(0.110);
    scalar sr_bar = scalar(1) + Foam::pow(lambda * sr, 2);
    scalar muplasma = scalar(0.00096);
    scalar m, n, eta, muRBC;
    if (sr_bar >= scalar(1.5))
    {
        m = scalar(122.28) * Foam::pow(alphaRBC, 3) + scalar(-51.213) * Foam::pow(alphaRBC, 2) +
            scalar(16.305) * alphaRBC + scalar(1);
        n = scalar(0.8092) * Foam::pow(alphaRBC, 3) + scalar(-0.8246) * Foam::pow(alphaRBC, 2) +
            scalar(-0.3503) * alphaRBC + scalar(1);
    }
    else
    {
        scalar k0 = Foam::log(Foam::log(sr_bar)) / Foam::log(sr_bar);
        m = scalar(70.782) * Foam::pow(alphaRBC, 3) + scalar(-22.454) * Foam::pow(alphaRBC, 2) +
            scalar(9.7193) * alphaRBC + scalar(1);
        n = (scalar(-0.8913) * Foam::pow(alphaRBC, 3) + scalar(2.0679) * Foam::pow(alphaRBC, 2) +
             scalar(-1.7814) * alphaRBC) *
                k0 +
            scalar(1);
    }
    eta = m * Foam::pow(1 + sr_bar, (n - scalar(1)) / scalar(2));
    muRBC = (eta * muplasma - alphaplasma * muplasma) / alphaRBC;
    // Temperature Correction
    scalar alphaT = scalar(1.92), betaT = scalar(0.20), phiT = scalar(17.42), xiT = scalar(14.1);
    scalar correction37 = alphaT + phiT / (scalar(1) + Foam::exp(betaT * (37 - xiT)));
    scalar correctionT = alphaT + phiT / (scalar(1) + Foam::exp(betaT * (T - xiT)));
    muRBC = muRBC * (correctionT / correction37);
    return muRBC;
}

template <class Thermo>
inline Foam::scalar Foam::bloodRBCTempTransport<Thermo>::kappa(const scalar p, const scalar T, const scalar sr,
                                                               const scalar alphaplasma) const
{
    return this->Cp(p, T) * mu(p, T, sr, alphaplasma) * rPr_;
}

template <class Thermo>
inline Foam::scalar Foam::bloodRBCTempTransport<Thermo>::alphah(const scalar p, const scalar T, const scalar sr,
                                                                const scalar alphaplasma) const
{
    return mu(p, T, sr, alphaplasma) * rPr_;
}

// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template <class Thermo>
inline void Foam::bloodRBCTempTransport<Thermo>::operator+=(const bloodRBCTempTransport<Thermo> &st)
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

template <class Thermo> inline void Foam::bloodRBCTempTransport<Thermo>::operator*=(const scalar s)
{
    Thermo::operator*=(s);
}

// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

template <class Thermo>
inline Foam::bloodRBCTempTransport<Thermo> Foam::operator+(const bloodRBCTempTransport<Thermo> &ct1,
                                                           const bloodRBCTempTransport<Thermo> &ct2)
{
    Thermo t(static_cast<const Thermo &>(ct1) + static_cast<const Thermo &>(ct2));

    if (mag(t.Y()) < SMALL)
    {
        return bloodRBCTempTransport<Thermo>(t, 0, ct1.rPr_);
    }
    else
    {
        scalar Y1 = ct1.Y() / t.Y();
        scalar Y2 = ct2.Y() / t.Y();

        return bloodRBCTempTransport<Thermo>(t, Y1 * ct1.mu_ + Y2 * ct2.mu_, 1.0 / (Y1 / ct1.rPr_ + Y2 / ct2.rPr_));
    }
}

template <class Thermo>
inline Foam::bloodRBCTempTransport<Thermo> Foam::operator*(const scalar s, const bloodRBCTempTransport<Thermo> &ct)
{
    return bloodRBCTempTransport<Thermo>(s * static_cast<const Thermo &>(ct), ct.mu_, 1.0 / ct.rPr_);
}

// ************************************************************************* //
