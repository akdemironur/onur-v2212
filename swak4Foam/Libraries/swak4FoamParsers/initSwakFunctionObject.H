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

Class
    initSwakFunctionObject

Description
    Basis for the other function objects here. Evaluates the most common options

SourceFiles
    initSwakFunctionObject.C

Contributors/Copyright:
    2008-2014, 2016-2018 Bernhard F.W. Gschaider <bgschaid@hfd-research.com>

 SWAK Revision: $Id$
\*---------------------------------------------------------------------------*/

#ifndef initSwakFunctionObject_H
#define initSwakFunctionObject_H

#include "fileName.H"
#include "functionObject.H"
#include "dictionary.H"
#include "OFstream.H"
#include "HashPtrTable.H"
#include "boolList.H"
#include "Field.H"

#include "swak.H"
#include "switchableNotImplemented.H"

#include "polyMesh.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                           Class initSwakFunctionObject Declaration
\*---------------------------------------------------------------------------*/

    class objectRegistry;

class initSwakFunctionObject
:
    public functionObject
{
    // Private Member Functions

    //- Disallow default bitwise copy construct
    initSwakFunctionObject(const initSwakFunctionObject&);

    //- Disallow default bitwise assignment
    void operator=(const initSwakFunctionObject&);

    // Private data

    dictionary dict_;

public:

    //- Runtime type information
    TypeName("initSwakFunctionObject");


    // Constructors

    //- Construct from components
    initSwakFunctionObject
    (
        const word&,
        const Time&,
        const dictionary&
    );


    // Member Functions

    //- start is called at the start of the time-loop
    virtual bool start();

    //- execute is called at each ++ or += of the time-loop
    virtual bool execute(const bool forceWrite);

#ifdef FOAM_FUNCTION_OBJECTS_NEEDS_FIELDS_METHOD
    wordList fields() const {
        return wordList();
    }
#endif

#ifdef FOAM_FUNCTIONOBJECT_EXECUTE_HAS_NO_FORCE
    //- Interface for old functionObject
    virtual bool execute();
#endif

#ifdef FOAM_FUNCTIONOBJECT_HAS_SEPARATE_WRITE_METHOD_AND_NO_START
    //- Interface for new functionObject
    virtual bool execute();
    virtual bool write();
#endif

    //- Read and set the function object if it's data has changed
    virtual bool read(const dictionary& dict);

#ifdef FOAM_FUNCTIONOBJECT_NEEDS_UPDATEMESH

#ifndef FOAM_FUNCTION_OBJECTS_HAS_NO_UPDATE_MESH
    // make functionObject happy but fail because this is not an implementation
    virtual void updateMesh(const mapPolyMesh&) {
        switchableNotImplemented(
            "initSwakFunctionObject::updateMesh",
            dict_
        );
    }
#endif

    // make functionObject happy but fail because this is not an implementation
    virtual void movePoints(
#ifdef FOAM_MOVEPOINTS_GETS_POLYMESH
        const polyMesh&
#else
        const pointField&
#endif
    ) {
        switchableNotImplemented(
            "initSwakFunctionObject::movePoints",
            dict_
        );
    }
#endif

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
