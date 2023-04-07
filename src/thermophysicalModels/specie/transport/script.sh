cp -r blood bloodPlasmaTemp
cd bloodPlasmaTemp
mv bloodTransport.C bloodPlasmaTempTransport.C
mv bloodTransport.H bloodPlasmaTempTransport.H
mv bloodTransportI.H bloodPlasmaTempTransportI.H
sed -i s/bloodTransport/bloodPlasmaTempTransport/g bloodPlasmaTempTransport*
sed -i s/"blood<"/"bloodPlasmaTemp<"/g bloodPlasmaTempTransport.H
cd ../..
cd include
