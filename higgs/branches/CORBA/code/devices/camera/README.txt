   Estos programas cliente/servidor para transmitir imágenes 
de un ordenador servidor remoto a otros ordenadores clientes
a través de CORBA funcionan utilizando la pila de firewire
antigua del kernel de Linux (ieee1394), pero no funcionan
correctamente utilizando la pila de firewire nueva (firewire).

Para instalar la pila antigua usamos los paquetes:
- Código fuente ieee1394 para kernel 2.6.31:
   ieee1394-2.6.31-8.fc12.src.rpm
-  Módulos compilados para kernel 2.6.31.6-166.PAE:
   ieee1394-kmdl-2.6.31.6-166.fc12.PAE-2.6.31-8.fc12.i686.rpm

   El programa servidor necesita ejecutarse con privilegios
de root para que pueda acceder al firewire.

Actualización [26/01/2010]:
  Con el kernel 2.6.31.12-174.2.3 de Fedora 12, la cámara ya
funciona con la pila de firewire nueva (firewire), con lo que
ya no hace falta recompilar la pila de firewire antigua.

   Adolfo Hernando

