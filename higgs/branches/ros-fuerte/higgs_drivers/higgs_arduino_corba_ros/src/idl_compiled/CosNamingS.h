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

#ifndef _TAO_IDL_COSNAMINGS_H_
#define _TAO_IDL_COSNAMINGS_H_


#include "CosNamingC.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "tao/Collocation_Proxy_Broker.h"
#include "tao/PortableServer/PortableServer.h"
#include "tao/PortableServer/Servant_Base.h"

// TAO_IDL - Generated from
// ../../../ACE_wrappers/TAO/TAO_IDL/be/be_visitor_module/module_sh.cpp:49

namespace POA_CosNaming
{
  
  
  // TAO_IDL - Generated from
  // ../../../ACE_wrappers/TAO/TAO_IDL/be/be_visitor_interface/interface_sh.cpp:87
  
  class NamingContext;
  typedef NamingContext *NamingContext_ptr;
  
  class  NamingContext
    : public virtual PortableServer::ServantBase
  {
  protected:
    NamingContext (void);
  
  public:
    // Useful for template programming.
    typedef ::CosNaming::NamingContext _stub_type;
    typedef ::CosNaming::NamingContext_ptr _stub_ptr_type;
    typedef ::CosNaming::NamingContext_var _stub_var_type;
    
    NamingContext (const NamingContext& rhs);
    virtual ~NamingContext (void);
    
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
    
    ::CosNaming::NamingContext *_this (void);
    
    virtual const char* _interface_repository_id (void) const;
    
    // TAO_IDL - Generated from
    // ../../../ACE_wrappers/TAO/TAO_IDL/be/be_visitor_operation/operation_sh.cpp:45
    
    virtual void bind (
        const ::CosNaming::Name & n,
        ::CORBA::Object_ptr obj) = 0;
    
    static void bind_skel (
        TAO_ServerRequest & server_request,
        void * servant_upcall,
        void * servant
      );
    
    // TAO_IDL - Generated from
    // ../../../ACE_wrappers/TAO/TAO_IDL/be/be_visitor_operation/operation_sh.cpp:45
    
    virtual void rebind (
        const ::CosNaming::Name & n,
        ::CORBA::Object_ptr obj) = 0;
    
    static void rebind_skel (
        TAO_ServerRequest & server_request,
        void * servant_upcall,
        void * servant
      );
    
    // TAO_IDL - Generated from
    // ../../../ACE_wrappers/TAO/TAO_IDL/be/be_visitor_operation/operation_sh.cpp:45
    
    virtual void bind_context (
        const ::CosNaming::Name & n,
        ::CosNaming::NamingContext_ptr nc) = 0;
    
    static void bind_context_skel (
        TAO_ServerRequest & server_request,
        void * servant_upcall,
        void * servant
      );
    
    // TAO_IDL - Generated from
    // ../../../ACE_wrappers/TAO/TAO_IDL/be/be_visitor_operation/operation_sh.cpp:45
    
    virtual void rebind_context (
        const ::CosNaming::Name & n,
        ::CosNaming::NamingContext_ptr nc) = 0;
    
    static void rebind_context_skel (
        TAO_ServerRequest & server_request,
        void * servant_upcall,
        void * servant
      );
    
    // TAO_IDL - Generated from
    // ../../../ACE_wrappers/TAO/TAO_IDL/be/be_visitor_operation/operation_sh.cpp:45
    
    virtual ::CORBA::Object_ptr resolve (
        const ::CosNaming::Name & n) = 0;
    
    static void resolve_skel (
        TAO_ServerRequest & server_request,
        void * servant_upcall,
        void * servant
      );
    
    // TAO_IDL - Generated from
    // ../../../ACE_wrappers/TAO/TAO_IDL/be/be_visitor_operation/operation_sh.cpp:45
    
    virtual void unbind (
        const ::CosNaming::Name & n) = 0;
    
    static void unbind_skel (
        TAO_ServerRequest & server_request,
        void * servant_upcall,
        void * servant
      );
    
    // TAO_IDL - Generated from
    // ../../../ACE_wrappers/TAO/TAO_IDL/be/be_visitor_operation/operation_sh.cpp:45
    
    virtual ::CosNaming::NamingContext_ptr new_context (
        void) = 0;
    
    static void new_context_skel (
        TAO_ServerRequest & server_request,
        void * servant_upcall,
        void * servant
      );
    
    // TAO_IDL - Generated from
    // ../../../ACE_wrappers/TAO/TAO_IDL/be/be_visitor_operation/operation_sh.cpp:45
    
    virtual ::CosNaming::NamingContext_ptr bind_new_context (
        const ::CosNaming::Name & n) = 0;
    
    static void bind_new_context_skel (
        TAO_ServerRequest & server_request,
        void * servant_upcall,
        void * servant
      );
    
    // TAO_IDL - Generated from
    // ../../../ACE_wrappers/TAO/TAO_IDL/be/be_visitor_operation/operation_sh.cpp:45
    
    virtual void destroy (
        void) = 0;
    
    static void destroy_skel (
        TAO_ServerRequest & server_request,
        void * servant_upcall,
        void * servant
      );
    
    // TAO_IDL - Generated from
    // ../../../ACE_wrappers/TAO/TAO_IDL/be/be_visitor_operation/operation_sh.cpp:45
    
    virtual void list (
        ::CORBA::ULong how_many,
        ::CosNaming::BindingList_out bl,
        ::CosNaming::BindingIterator_out bi) = 0;
    
    static void list_skel (
        TAO_ServerRequest & server_request,
        void * servant_upcall,
        void * servant
      );
  };
  
  // TAO_IDL - Generated from
  // ../../../ACE_wrappers/TAO/TAO_IDL/be/be_visitor_interface/interface_sh.cpp:87
  
  class BindingIterator;
  typedef BindingIterator *BindingIterator_ptr;
  
  class  BindingIterator
    : public virtual PortableServer::ServantBase
  {
  protected:
    BindingIterator (void);
  
  public:
    // Useful for template programming.
    typedef ::CosNaming::BindingIterator _stub_type;
    typedef ::CosNaming::BindingIterator_ptr _stub_ptr_type;
    typedef ::CosNaming::BindingIterator_var _stub_var_type;
    
    BindingIterator (const BindingIterator& rhs);
    virtual ~BindingIterator (void);
    
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
    
    ::CosNaming::BindingIterator *_this (void);
    
    virtual const char* _interface_repository_id (void) const;
    
    // TAO_IDL - Generated from
    // ../../../ACE_wrappers/TAO/TAO_IDL/be/be_visitor_operation/operation_sh.cpp:45
    
    virtual ::CORBA::Boolean next_one (
        ::CosNaming::Binding_out b) = 0;
    
    static void next_one_skel (
        TAO_ServerRequest & server_request,
        void * servant_upcall,
        void * servant
      );
    
    // TAO_IDL - Generated from
    // ../../../ACE_wrappers/TAO/TAO_IDL/be/be_visitor_operation/operation_sh.cpp:45
    
    virtual ::CORBA::Boolean next_n (
        ::CORBA::ULong how_many,
        ::CosNaming::BindingList_out bl) = 0;
    
    static void next_n_skel (
        TAO_ServerRequest & server_request,
        void * servant_upcall,
        void * servant
      );
    
    // TAO_IDL - Generated from
    // ../../../ACE_wrappers/TAO/TAO_IDL/be/be_visitor_operation/operation_sh.cpp:45
    
    virtual void destroy (
        void) = 0;
    
    static void destroy_skel (
        TAO_ServerRequest & server_request,
        void * servant_upcall,
        void * servant
      );
  };
  
  // TAO_IDL - Generated from
  // ../../../ACE_wrappers/TAO/TAO_IDL/be/be_visitor_interface/interface_sh.cpp:87
  
  class NamingContextExt;
  typedef NamingContextExt *NamingContextExt_ptr;
  
  class  NamingContextExt
    : public virtual POA_CosNaming::NamingContext
  {
  protected:
    NamingContextExt (void);
  
  public:
    // Useful for template programming.
    typedef ::CosNaming::NamingContextExt _stub_type;
    typedef ::CosNaming::NamingContextExt_ptr _stub_ptr_type;
    typedef ::CosNaming::NamingContextExt_var _stub_var_type;
    
    NamingContextExt (const NamingContextExt& rhs);
    virtual ~NamingContextExt (void);
    
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
    
    ::CosNaming::NamingContextExt *_this (void);
    
    virtual const char* _interface_repository_id (void) const;
    
    // TAO_IDL - Generated from
    // ../../../ACE_wrappers/TAO/TAO_IDL/be/be_visitor_operation/operation_sh.cpp:45
    
    virtual char * to_string (
        const ::CosNaming::Name & n) = 0;
    
    static void to_string_skel (
        TAO_ServerRequest & server_request,
        void * servant_upcall,
        void * servant
      );
    
    // TAO_IDL - Generated from
    // ../../../ACE_wrappers/TAO/TAO_IDL/be/be_visitor_operation/operation_sh.cpp:45
    
    virtual ::CosNaming::Name * to_name (
        const char * sn) = 0;
    
    static void to_name_skel (
        TAO_ServerRequest & server_request,
        void * servant_upcall,
        void * servant
      );
    
    // TAO_IDL - Generated from
    // ../../../ACE_wrappers/TAO/TAO_IDL/be/be_visitor_operation/operation_sh.cpp:45
    
    virtual char * to_url (
        const char * addr,
        const char * sn) = 0;
    
    static void to_url_skel (
        TAO_ServerRequest & server_request,
        void * servant_upcall,
        void * servant
      );
    
    // TAO_IDL - Generated from
    // ../../../ACE_wrappers/TAO/TAO_IDL/be/be_visitor_operation/operation_sh.cpp:45
    
    virtual ::CORBA::Object_ptr resolve_str (
        const char * n) = 0;
    
    static void resolve_str_skel (
        TAO_ServerRequest & server_request,
        void * servant_upcall,
        void * servant
      );
    
    // TAO_IDL - Generated from
    // ../../../ACE_wrappers/TAO/TAO_IDL/be/be_interface.cpp:2037
    
    static void
    bind_skel (
        TAO_ServerRequest & server_request, 
        void * servant_upcall,
        void * servant
      );
    
    // TAO_IDL - Generated from
    // ../../../ACE_wrappers/TAO/TAO_IDL/be/be_interface.cpp:2037
    
    static void
    rebind_skel (
        TAO_ServerRequest & server_request, 
        void * servant_upcall,
        void * servant
      );
    
    // TAO_IDL - Generated from
    // ../../../ACE_wrappers/TAO/TAO_IDL/be/be_interface.cpp:2037
    
    static void
    bind_context_skel (
        TAO_ServerRequest & server_request, 
        void * servant_upcall,
        void * servant
      );
    
    // TAO_IDL - Generated from
    // ../../../ACE_wrappers/TAO/TAO_IDL/be/be_interface.cpp:2037
    
    static void
    rebind_context_skel (
        TAO_ServerRequest & server_request, 
        void * servant_upcall,
        void * servant
      );
    
    // TAO_IDL - Generated from
    // ../../../ACE_wrappers/TAO/TAO_IDL/be/be_interface.cpp:2037
    
    static void
    resolve_skel (
        TAO_ServerRequest & server_request, 
        void * servant_upcall,
        void * servant
      );
    
    // TAO_IDL - Generated from
    // ../../../ACE_wrappers/TAO/TAO_IDL/be/be_interface.cpp:2037
    
    static void
    unbind_skel (
        TAO_ServerRequest & server_request, 
        void * servant_upcall,
        void * servant
      );
    
    // TAO_IDL - Generated from
    // ../../../ACE_wrappers/TAO/TAO_IDL/be/be_interface.cpp:2037
    
    static void
    new_context_skel (
        TAO_ServerRequest & server_request, 
        void * servant_upcall,
        void * servant
      );
    
    // TAO_IDL - Generated from
    // ../../../ACE_wrappers/TAO/TAO_IDL/be/be_interface.cpp:2037
    
    static void
    bind_new_context_skel (
        TAO_ServerRequest & server_request, 
        void * servant_upcall,
        void * servant
      );
    
    // TAO_IDL - Generated from
    // ../../../ACE_wrappers/TAO/TAO_IDL/be/be_interface.cpp:2037
    
    static void
    destroy_skel (
        TAO_ServerRequest & server_request, 
        void * servant_upcall,
        void * servant
      );
    
    // TAO_IDL - Generated from
    // ../../../ACE_wrappers/TAO/TAO_IDL/be/be_interface.cpp:2037
    
    static void
    list_skel (
        TAO_ServerRequest & server_request, 
        void * servant_upcall,
        void * servant
      );
  };

// TAO_IDL - Generated from
// ../../../ACE_wrappers/TAO/TAO_IDL/be/be_visitor_module/module_sh.cpp:80

} // module CosNaming

// TAO_IDL - Generated from 
// ../../../ACE_wrappers/TAO/TAO_IDL/be/be_codegen.cpp:1288


#if defined (__ACE_INLINE__)
#include "CosNamingS.inl"
#endif /* defined INLINE */

#endif /* ifndef */

