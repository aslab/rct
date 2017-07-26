$Id:$
-----------------------------------------------------------------------------
-- This Readme file describe the intention and structure of Higgs folder
-----------------------------------------------------------------------------

INTENTION

-This folder contains all the ongoing work within the Higgs proyect within ASys::RCT,
which may include documents, RSA models, simulation environments and code.

The Higgs repository directory is mainly that, a directory containing all the work being
developed in the framework of Higgs. It is not intended to be an eclipse code project,
but it may contain a .project if someone checked-out it all, for example to modify this
README.txt

-----------------------------------

STRUCTURE:

Higgs
|
|-branches: directory that contains different lines of development for Higgs (i.e. CORBA line)
|
|-docs : this folder contains document projects, may they be eclipse LaTeX project,
|        or simply raw eclipse projects containing word or other text files
|        to work in one of the docs check-out its folder (it will usually contain a .project file)
|
|-hardware: directory that contains resources to used to develop some Higgs physical components
|
|-sims : this folder contains the webots simulation world
|
|-tags : this directory contains frozen partial versions of trunk that provide some stable functionality
|
|-trunk: this directory contains current delopment of the Higgs system
|    -code   : this folder contains the code implementing the Higgs system. It is divided into
|              independent folders each one being a separate project containing a
|              functional component.
|    -models : folder that contains the current Higgs RSA models
                  
