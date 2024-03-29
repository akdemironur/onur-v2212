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
    writeOldTimesOnSignalFunctionObject

Description
    This function object tries to record old fields and writes them in
    case of a Signal

SourceFiles
    writeOldTimesOnSignalFunctionObject.C

Contributors/Copyright:
    2014-2018, 2020 Bernhard F.W. Gschaider <bgschaid@hfd-research.com>

 SWAK Revision: $Id$
\*---------------------------------------------------------------------------*/

#ifndef writeOldTimesOnSignalFunctionObject_H
#define writeOldTimesOnSignalFunctionObject_H

#include "functionObject.H"
#include "dictionary.H"
#include "TimeCloneList.H"
#include "DynamicList.H"

#include <signal.h>

#include "swak.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                           Class writeOldTimesOnSignalFunctionObject Declaration
\*---------------------------------------------------------------------------*/

    class objectRegistry;

class writeOldTimesOnSignalFunctionObject
:
    public functionObject
{
    // Private Member Functions

    //- Disallow default bitwise copy construct
    writeOldTimesOnSignalFunctionObject(const writeOldTimesOnSignalFunctionObject&);

    //- Disallow default bitwise assignment
    void operator=(const writeOldTimesOnSignalFunctionObject&);

    const dictionary &dict_;

    TimeCloneList times_;

    const Time &theTime_;

    class SignalHandlerInfo {
    protected:
        struct sigaction oldAction_;
        word name_;
        int sig_;
        bool set_;
    public:
        SignalHandlerInfo(
            word name,
            int sig
        );

        SignalHandlerInfo()
            :
            name_("nix"),
            sig_(-1),
            set_(false)
            {}

        void resetHandler();

        ~SignalHandlerInfo() {};

        int sig() const
           { return sig_; }

        bool set() const
           { return set_; }

    };

    static void sigHandler(int);

    static writeOldTimesOnSignalFunctionObject *singleton_;

    DynamicList<SignalHandlerInfo> handlers_;

    bool writeCurrent_;

    scalar sleepSecondsBeforeReraising_;

    bool sigFPE_;
    bool sigSEGV_;
    bool sigINT_;
    bool sigTERM_;
    bool sigQUIT_;
    bool sigUSR1_;
    bool sigUSR2_;
    bool sigABRT_;

    bool alreadyDumped_;

    bool itWasMeWhoReraised_;

#ifdef FOAM_FUNCTIONOBJECT_HAS_SEPARATE_WRITE_METHOD_AND_NO_START
    bool needsInit_;
#endif

    label lastStepExecute_;

public:

    //- Runtime type information
    TypeName("writeOldTimesOnSignal");


    // Constructors

    //- Construct from components
    writeOldTimesOnSignalFunctionObject
    (
        const word&,
        const Time&,
        const dictionary&
    );


    // Member Functions

    //- start is called at the start of the time-loop
    virtual bool start();

    //- execute is called at each ++ or += of the time-loop
#ifdef FOAM_FUNCTIONOBJECT_EXECUTE_HAS_NO_FORCE
    virtual bool execute();
#else
    virtual bool execute(const bool forceWrite);

#ifdef FOAM_FUNCTIONOBJECT_HAS_SEPARATE_WRITE_METHOD_AND_NO_START
    virtual bool execute() {
        return execute(false);
    }

    virtual bool write() {
        return execute(true);
    }
#endif
#endif


    //- Read and set the function object if it's data has changed
    virtual bool read(const dictionary& dict);

#ifdef FOAM_FUNCTIONOBJECT_NEEDS_UPDATEMESH

#ifndef FOAM_FUNCTION_OBJECTS_HAS_NO_UPDATE_MESH
    virtual void updateMesh(const mapPolyMesh&) {
    }
#endif

    virtual void movePoints(
#ifdef FOAM_MOVEPOINTS_GETS_POLYMESH
        const polyMesh&
#else
        const pointField&
#endif
    ) {
    }
#endif

#ifdef FOAM_FUNCTION_OBJECTS_NEEDS_FIELDS_METHOD
    wordList fields() const {
        return wordList();
    }
#endif

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
