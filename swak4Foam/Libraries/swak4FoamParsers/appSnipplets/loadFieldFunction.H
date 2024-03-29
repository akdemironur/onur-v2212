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

Description
    Load a field into memory if it exists

Contributors/Copyright:
    2010-2013, 2016, 2018 Bernhard F.W. Gschaider <bgschaid@hfd-research.com>

 SWAK Revision: $Id$
\*---------------------------------------------------------------------------*/

template<class FieldType>
bool loadFieldFunction(
    fvMesh &mesh,
    const word &fName,
    SLPtrList<FieldType> &fieldList
) {
    const Time &runTime=mesh.time();

    IOobject f
        (
            fName,
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ,
            IOobject::NO_WRITE
        );
#ifdef FOAM_HAS_TYPE_HEADER_OK
#ifdef FOAM_TYPE_HEADER_OK_IS_PROTECTED
    f.headerOk();
#else
    f.typeHeaderOk<FieldType>(false);
#endif
#else
    f.headerOk();
#endif

    word className=f.headerClassName();

    if(className==FieldType::typeName) {
        Info << "Reading field " << fName << " of type "
            << FieldType::typeName << endl;
        fieldList.append(
            new FieldType
            (
                IOobject
                (
                    fName,
                    runTime.timeName(),
                    mesh,
                    IOobject::MUST_READ,
                    IOobject::AUTO_WRITE
                ),
                mesh
            )
        );
        return true;
    } else {
        return false;
    }
}

template<class FieldType>
bool loadPointFieldFunction(
    fvMesh &mesh,
    pointMesh &pMesh,
    const word &fName,
    SLPtrList<FieldType> &fieldList
) {
    const Time &runTime=mesh.time();

    IOobject f
        (
            fName,
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ,
            IOobject::NO_WRITE
        );
#ifdef FOAM_HAS_TYPE_HEADER_OK
#ifdef FOAM_TYPE_HEADER_OK_IS_PROTECTED
    f.headerOk();
#else
    f.typeHeaderOk<FieldType>(false);
#endif
#else
    f.headerOk();
#endif

    word className=f.headerClassName();

    if(className==FieldType::typeName) {
        Info << "Reading field " << fName << " of type "
            << FieldType::typeName << endl;
        fieldList.append(
            new FieldType
            (
                IOobject
                (
                    fName,
                    runTime.timeName(),
                    mesh,
                    IOobject::MUST_READ,
                    IOobject::AUTO_WRITE
                ),
                pMesh
            )
        );
        return true;
    } else {
        return false;
    }
}

template<class FieldType>
string reloadFieldsFunction(
    fvMesh &mesh,
    SLPtrList<FieldType> &fieldList
) {
    if(fieldList.size()<=0) {
        return "";
    }
    const Time &runTime=mesh.time();
    string result="Reloading type "+FieldType::typeName+": ";

    forAllIter(typename SLPtrList<FieldType>,fieldList,i){
        FieldType &field=(*i);
        const word &fName=field.name();
        result+=fName+" ";

        IOobject f
            (
                fName,
                runTime.timeName(),
                mesh,
                IOobject::MUST_READ,
                IOobject::NO_WRITE
            );
        if(
#ifdef FOAM_HAS_TYPE_HEADER_OK
#ifdef FOAM_TYPE_HEADER_OK_IS_PROTECTED
            f.headerOk() &&
            f.headerClassName() == FieldType::typeName
#else
            f.typeHeaderOk<FieldType>(false)
#endif
#else
            f.headerOk()
#endif
        ) {
            word className=f.headerClassName();

            if(className==FieldType::typeName) {
                result+="ok ";
                FieldType newField(
                    IOobject
                    (
                        fName,
                        runTime.timeName(),
                        mesh,
                        IOobject::MUST_READ,
                        IOobject::AUTO_WRITE
                    ),
                    mesh
                );
                field==newField;
            } else {
                result+="wrong:"+className+" ";
            }
        } else {
            result+="missing ";
        }
        result+="...";
    }
    result+="\n";

    return result;
}


// ************************************************************************* //
