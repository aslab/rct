// -*- C++ -*-
//
// $Id$

// ****  Code generated by the The ACE ORB (TAO) IDL Compiler ****
// TAO and the TAO IDL Compiler have been developed by:
//       Center for Distributed Object Computing
//       Washington University
//       St. Louis, MO
//       USA
//       http://www.cs.wustl.edu/~schmidt/doc-center.html
// and
//       Distributed Object Computing Laboratory
//       University of California at Irvine
//       Irvine, CA
//       USA
//       http://doc.ece.uci.edu/
// and
//       Institute for Software Integrated Systems
//       Vanderbilt University
//       Nashville, TN
//       USA
//       http://www.isis.vanderbilt.edu/
//
// Information about TAO is available at:
//     http://www.cs.wustl.edu/~schmidt/TAO.html

// TAO_IDL - Generated from
// ../../../ACE_wrappers/TAO/TAO_IDL/be/be_codegen.cpp:487

#ifndef _TAO_IDL_ARDUINOS_H_
#define _TAO_IDL_ARDUINOS_H_


#include "ArduinoC.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "tao/Collocation_Proxy_Broker.h"
#include "tao/PortableServer/PortableServer.h"
#include "tao/PortableServer/Servant_Base.h"

// TAO_IDL - Generated from
// ../../../ACE_wrappers/TAO/TAO_IDL/be/be_visitor_module/module_sh.cpp:49

namespace POA_higgs
{
  
  
  // TAO_IDL - Generated from
  // ../../../ACE_wrappers/TAO/TAO_IDL/be/be_visitor_interface/interface_sh.cpp:87
  
  class Arduino;
  typedef Arduino *Arduino_ptr;
  
  class  Arduino
    : public virtual PortableServer::ServantBase
  {
  protected:
    Arduino (void);
  
  public:
    // Useful for template programming.
    typedef ::higgs::Arduino _stub_type;
    typedef ::higgs::Arduino_ptr _stub_ptr_type;
    typedef ::higgs::Arduino_var _stub_var_type;
    
    Arduino (const Arduino& rhs);
    virtual ~Arduino (void);
    
    virtual ::CORBA::Boolean _is_a (const char* logical_type_id);
    
    static void _is_a_skel (
        TAO_ServerRequest & req,
        void * servant_upcall,
        void * servant
      );
    
    static void _non_existent_skel (
        TAO_ServerRequest & req,
        void * servant_upcall,
        void * servant
      );
    
    static void _interface_skel (
        TAO_ServerRequest & req,
        void * servant_upcall,
        void * servant
      );
    
    static void _component_skel (
        TAO_ServerRequest & req,
        void * servant_upcall,
        void * servant
      );
    
    static void _repository_id_skel (
        TAO_ServerRequest & req,
        void * servant_upcall,
        void * servant);
    
    virtual void _dispatch (
        TAO_ServerRequest & req,
        void * servant_upcall);
    
    ::higgs::Arduino *_this (void);
    
    virtual const char* _interface_repository_id (void) const;
    
    // TAO_IDL - Generated from
    // ../../../ACE_wrappers/TAO/TAO_IDL/be/be_visitor_operation/operation_sh.cpp:45
    
    virtual void cambiarReferencia (
        ::higgs::Referencia ref) = 0;
    
    static void cambiarReferencia_skel (
        TAO_ServerRequest & server_request,
        void * servant_upcall,
        void * servant
      );
    
    // TAO_IDL - Generated from
    // ../../../ACE_wrappers/TAO/TAO_IDL/be/be_visitor_operation/operation_sh.cpp:45
    
    virtual void encenderPin (
        ::higgs::Pin p) = 0;
    
    static void encenderPin_skel (
        TAO_ServerRequest & server_request,
        void * servant_upcall,
        void * servant
      );
    
    // TAO_IDL - Generated from
    // ../../../ACE_wrappers/TAO/TAO_IDL/be/be_visitor_operation/operation_sh.cpp:45
    
    virtual void apagarPin (
        ::higgs::Pin p) = 0;
    
    static void apagarPin_skel (
        TAO_ServerRequest & server_request,
        void * servant_upcall,
        void * servant
      );
    
    // TAO_IDL - Generated from
    // ../../../ACE_wrappers/TAO/TAO_IDL/be/be_visitor_operation/operation_sh.cpp:45
    
    virtual ::higgs::iv_data iv_motors (
        void) = 0;
    
    static void iv_motors_skel (
        TAO_ServerRequest & server_request,
        void * servant_upcall,
        void * servant
      );
    
    // TAO_IDL - Generated from
    // ../../../ACE_wrappers/TAO/TAO_IDL/be/be_visitor_operation/operation_sh.cpp:45
    
    virtual ::higgs::iv_data iv_instrumentation (
        void) = 0;
    
    static void iv_instrumentation_skel (
        TAO_ServerRequest & server_request,
        void * servant_upcall,
        void * servant
      );
    
    // TAO_IDL - Generated from
    // ../../../ACE_wrappers/TAO/TAO_IDL/be/be_visitor_operation/operation_sh.cpp:45
    
    virtual ::higgs::iv_data iv_vaio (
        void) = 0;
    
    static void iv_vaio_skel (
        TAO_ServerRequest & server_request,
        void * servant_upcall,
        void * servant
      );
    
    // TAO_IDL - Generated from
    // ../../../ACE_wrappers/TAO/TAO_IDL/be/be_visitor_operation/operation_sh.cpp:45
    
    virtual ::CORBA::Double brujula (
        void) = 0;
    
    static void brujula_skel (
        TAO_ServerRequest & server_request,
        void * servant_upcall,
        void * servant
      );
    
    // TAO_IDL - Generated from
    // ../../../ACE_wrappers/TAO/TAO_IDL/be/be_visitor_operation/operation_sh.cpp:45
    
    virtual void acelerometro (
        ::CORBA::Double_out x,
        ::CORBA::Double_out y) = 0;
    
    static void acelerometro_skel (
        TAO_ServerRequest & server_request,
        void * servant_upcall,
        void * servant
      );
    
    // TAO_IDL - Generated from
    // ../../../ACE_wrappers/TAO/TAO_IDL/be/be_visitor_operation/operation_sh.cpp:45
    
    virtual void TurnOn (
        ::higgs::Device dev) = 0;
    
    static void TurnOn_skel (
        TAO_ServerRequest & server_request,
        void * servant_upcall,
        void * servant
      );
    
    // TAO_IDL - Generated from
    // ../../../ACE_wrappers/TAO/TAO_IDL/be/be_visitor_operation/operation_sh.cpp:45
    
    virtual void TurnOff (
        ::higgs::Device dev) = 0;
    
    static void TurnOff_skel (
        TAO_ServerRequest & server_request,
        void * servant_upcall,
        void * servant
      );
  };

// TAO_IDL - Generated from
// ../../../ACE_wrappers/TAO/TAO_IDL/be/be_visitor_module/module_sh.cpp:80

} // module higgs

// TAO_IDL - Generated from 
// ../../../ACE_wrappers/TAO/TAO_IDL/be/be_codegen.cpp:1288


#if defined (__ACE_INLINE__)
#include "ArduinoS.inl"
#endif /* defined INLINE */

#endif /* ifndef */
