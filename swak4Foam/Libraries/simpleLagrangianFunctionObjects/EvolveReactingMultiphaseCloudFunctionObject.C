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
    2012-2013, 2015-2016, 2018 Bernhard F.W. Gschaider <bgschaid@hfd-research.com>

 SWAK Revision: $Id:  $
\*---------------------------------------------------------------------------*/

#include "EvolveReactingMultiphaseCloudFunctionObject.H"
#include "addToRunTimeSelectionTable.H"

#include "polyMesh.H"
#include "IOmanip.H"
#include "swakTime.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{

#ifdef FOAM_REACTINGCLOUD_TEMPLATED
    addNamedTemplateToRunTimeSelectionTable
    (
        functionObject,
        EvolveReactingMultiphaseCloudFunctionObject,
        constThermoReactingMultiphaseCloud,
        dictionary,
        evolveConstReactingMultiphaseCloud
    );

    defineTemplateTypeNameAndDebug(EvolveReactingMultiphaseCloudFunctionObject<constThermoReactingMultiphaseCloud>, 0);
    typedef EvolveCloudFunctionObject<constThermoReactingMultiphaseCloud> constThermoReactingMultiphaseEvolveCloudFunctionObject;
    defineTemplateTypeNameAndDebug(constThermoReactingMultiphaseEvolveCloudFunctionObject, 0);

    addNamedTemplateToRunTimeSelectionTable
    (
        functionObject,
        EvolveReactingMultiphaseCloudFunctionObject,
        thermoReactingMultiphaseCloud,
        dictionary,
        evolveThermoReactingMultiphaseCloud
    );

    defineTemplateTypeNameAndDebug(EvolveReactingMultiphaseCloudFunctionObject<thermoReactingMultiphaseCloud>, 0);
    typedef EvolveCloudFunctionObject<thermoReactingMultiphaseCloud> thermoReactingMultiphaseEvolveCloudFunctionObject;
    defineTemplateTypeNameAndDebug(thermoReactingMultiphaseEvolveCloudFunctionObject, 0);

    addNamedTemplateToRunTimeSelectionTable
    (
        functionObject,
        EvolveReactingMultiphaseCloudFunctionObject,
        icoPoly8ThermoReactingMultiphaseCloud,
        dictionary,
        evolveIcoPoly8ReactingMultiphaseCloud
    );

    defineTemplateTypeNameAndDebug(EvolveReactingMultiphaseCloudFunctionObject<icoPoly8ThermoReactingMultiphaseCloud>, 0);
    typedef EvolveCloudFunctionObject<icoPoly8ThermoReactingMultiphaseCloud> icoPoly8ThermoReactingMultiphaseEvolveCloudFunctionObject;
    defineTemplateTypeNameAndDebug(icoPoly8ThermoReactingMultiphaseEvolveCloudFunctionObject, 0);
#else
    defineTypeNameAndDebug(EvolveReactingMultiphaseCloudFunctionObject, 0);
    typedef EvolveCloudFunctionObject<basicReactingMultiphaseCloud> reactingMultiphaseEvolveCloudFunctionObject;
    defineTemplateTypeNameAndDebug(reactingMultiphaseEvolveCloudFunctionObject, 0);

    addNamedToRunTimeSelectionTable
    (
        functionObject,
        EvolveReactingMultiphaseCloudFunctionObject,
        dictionary,
        evolveReactingMultiphaseCloud
    );
#endif

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

#ifdef FOAM_REACTINGCLOUD_TEMPLATED
template <class CloudType>
EvolveReactingMultiphaseCloudFunctionObject<CloudType>
#else
EvolveReactingMultiphaseCloudFunctionObject
#endif
::EvolveReactingMultiphaseCloudFunctionObject
(
    const word& name,
    const Time& t,
    const dictionary& dict
)
:
    EvolveCloudFunctionObject<
#ifdef FOAM_REACTINGCLOUD_TEMPLATED
    CloudType
#else
    basicReactingMultiphaseCloud
#endif
    >(
        name,
        t,
        dict
    )
{
#ifdef FOAM_FUNCTIONOBJECT_HAS_SEPARATE_WRITE_METHOD_AND_NO_START
    this->read(dict);
#endif
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

#ifdef FOAM_REACTINGCLOUD_TEMPLATED
#define TEMPLATE template
template <class CloudType>
bool EvolveReactingMultiphaseCloudFunctionObject<CloudType>
#else
#define TEMPLATE
bool EvolveReactingMultiphaseCloudFunctionObject
#endif
::start()
{
    this->cloud().reset(
#ifdef FOAM_REACTINGCLOUD_TEMPLATED
        new CloudType(
#else
        new basicReactingMultiphaseCloud(
#endif
            this->cloudName(),
            this->TEMPLATE getField<volScalarField>("rhoName"),
            this->TEMPLATE getField<volVectorField>("UName"),
            this->g(),
#ifdef FOAM_OLD_THERMOPHYSICS
            const_cast<basicThermo &>(
                this->template getField<basicThermo>("thermoPhysicsName")
            )
#else
            const_cast<SLGThermo &>(
                this->getField<SLGThermo>("SLGThermoPhysicsName")
            )
#endif
        )
    );

    return true;
}


} // namespace Foam

// ************************************************************************* //
