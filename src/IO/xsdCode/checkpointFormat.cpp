// Copyright (c) 2005-2014 Code Synthesis Tools CC
//
// This program was generated by CodeSynthesis XSD, an XML Schema to
// C++ data binding compiler.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
//
// In addition, as a special exception, Code Synthesis Tools CC gives
// permission to link this program with the Xerces-C++ library (or with
// modified versions of Xerces-C++ that use the same license as Xerces-C++),
// and distribute linked combinations including the two. You must obey
// the GNU General Public License version 2 in all respects for all of
// the code used other than Xerces-C++. If you modify this copy of the
// program, you may extend this exception to your version of the program,
// but you are not obligated to do so. If you do not wish to do so, delete
// this exception statement from your version.
//
// Furthermore, Code Synthesis Tools CC makes a special exception for
// the Free/Libre and Open Source Software (FLOSS) which is described
// in the accompanying FLOSSE file.
//

// Begin prologue.
//
//
// End prologue.

#include <xsd/cxx/pre.hxx>

#include "checkpointFormat.h"

// particle_t
// 

const particle_t::x_type& particle_t::
x () const
{
  return this->x_.get ();
}

particle_t::x_type& particle_t::
x ()
{
  return this->x_.get ();
}

void particle_t::
x (const x_type& x)
{
  this->x_.set (x);
}

void particle_t::
x (::std::unique_ptr< x_type > x)
{
  this->x_.set (std::move (x));
}

const particle_t::v_type& particle_t::
v () const
{
  return this->v_.get ();
}

particle_t::v_type& particle_t::
v ()
{
  return this->v_.get ();
}

void particle_t::
v (const v_type& x)
{
  this->v_.set (x);
}

void particle_t::
v (::std::unique_ptr< v_type > x)
{
  this->v_.set (std::move (x));
}

const particle_t::f_type& particle_t::
f () const
{
  return this->f_.get ();
}

particle_t::f_type& particle_t::
f ()
{
  return this->f_.get ();
}

void particle_t::
f (const f_type& x)
{
  this->f_.set (x);
}

void particle_t::
f (::std::unique_ptr< f_type > x)
{
  this->f_.set (std::move (x));
}

const particle_t::old_f_type& particle_t::
old_f () const
{
  return this->old_f_.get ();
}

particle_t::old_f_type& particle_t::
old_f ()
{
  return this->old_f_.get ();
}

void particle_t::
old_f (const old_f_type& x)
{
  this->old_f_.set (x);
}

void particle_t::
old_f (::std::unique_ptr< old_f_type > x)
{
  this->old_f_.set (std::move (x));
}

const particle_t::m_type& particle_t::
m () const
{
  return this->m_.get ();
}

particle_t::m_type& particle_t::
m ()
{
  return this->m_.get ();
}

void particle_t::
m (const m_type& x)
{
  this->m_.set (x);
}

void particle_t::
m (::std::unique_ptr< m_type > x)
{
  this->m_.set (std::move (x));
}

const particle_t::epsilon_type& particle_t::
epsilon () const
{
  return this->epsilon_.get ();
}

particle_t::epsilon_type& particle_t::
epsilon ()
{
  return this->epsilon_.get ();
}

void particle_t::
epsilon (const epsilon_type& x)
{
  this->epsilon_.set (x);
}

const particle_t::sigma_type& particle_t::
sigma () const
{
  return this->sigma_.get ();
}

particle_t::sigma_type& particle_t::
sigma ()
{
  return this->sigma_.get ();
}

void particle_t::
sigma (const sigma_type& x)
{
  this->sigma_.set (x);
}

const particle_t::type_type& particle_t::
type () const
{
  return this->type_.get ();
}

particle_t::type_type& particle_t::
type ()
{
  return this->type_.get ();
}

void particle_t::
type (const type_type& x)
{
  this->type_.set (x);
}

void particle_t::
type (::std::unique_ptr< type_type > x)
{
  this->type_.set (std::move (x));
}


// Checkpoint_t
// 

const Checkpoint_t::particle_sequence& Checkpoint_t::
particle () const
{
  return this->particle_;
}

Checkpoint_t::particle_sequence& Checkpoint_t::
particle ()
{
  return this->particle_;
}

void Checkpoint_t::
particle (const particle_sequence& s)
{
  this->particle_ = s;
}


#include <xsd/cxx/xml/dom/parsing-source.hxx>

// particle_t
//

particle_t::
particle_t (const x_type& x,
            const v_type& v,
            const f_type& f,
            const old_f_type& old_f,
            const m_type& m,
            const epsilon_type& epsilon,
            const sigma_type& sigma,
            const type_type& type)
: ::xml_schema::type (),
  x_ (x, this),
  v_ (v, this),
  f_ (f, this),
  old_f_ (old_f, this),
  m_ (m, this),
  epsilon_ (epsilon, this),
  sigma_ (sigma, this),
  type_ (type, this)
{
}

particle_t::
particle_t (::std::unique_ptr< x_type > x,
            ::std::unique_ptr< v_type > v,
            ::std::unique_ptr< f_type > f,
            ::std::unique_ptr< old_f_type > old_f,
            const m_type& m,
            const epsilon_type& epsilon,
            const sigma_type& sigma,
            const type_type& type)
: ::xml_schema::type (),
  x_ (std::move (x), this),
  v_ (std::move (v), this),
  f_ (std::move (f), this),
  old_f_ (std::move (old_f), this),
  m_ (m, this),
  epsilon_ (epsilon, this),
  sigma_ (sigma, this),
  type_ (type, this)
{
}

particle_t::
particle_t (const particle_t& x,
            ::xml_schema::flags f,
            ::xml_schema::container* c)
: ::xml_schema::type (x, f, c),
  x_ (x.x_, f, this),
  v_ (x.v_, f, this),
  f_ (x.f_, f, this),
  old_f_ (x.old_f_, f, this),
  m_ (x.m_, f, this),
  epsilon_ (x.epsilon_, f, this),
  sigma_ (x.sigma_, f, this),
  type_ (x.type_, f, this)
{
}

particle_t::
particle_t (const ::xercesc::DOMElement& e,
            ::xml_schema::flags f,
            ::xml_schema::container* c)
: ::xml_schema::type (e, f | ::xml_schema::flags::base, c),
  x_ (this),
  v_ (this),
  f_ (this),
  old_f_ (this),
  m_ (this),
  epsilon_ (this),
  sigma_ (this),
  type_ (this)
{
  if ((f & ::xml_schema::flags::base) == 0)
  {
    ::xsd::cxx::xml::dom::parser< char > p (e, true, false, false);
    this->parse (p, f);
  }
}

void particle_t::
parse (::xsd::cxx::xml::dom::parser< char >& p,
       ::xml_schema::flags f)
{
  for (; p.more_content (); p.next_content (false))
  {
    const ::xercesc::DOMElement& i (p.cur_element ());
    const ::xsd::cxx::xml::qualified_name< char > n (
      ::xsd::cxx::xml::dom::name< char > (i));

    // x
    //
    if (n.name () == "x" && n.namespace_ ().empty ())
    {
      ::std::unique_ptr< x_type > r (
        x_traits::create (i, f, this));

      if (!x_.present ())
      {
        this->x_.set (::std::move (r));
        continue;
      }
    }

    // v
    //
    if (n.name () == "v" && n.namespace_ ().empty ())
    {
      ::std::unique_ptr< v_type > r (
        v_traits::create (i, f, this));

      if (!v_.present ())
      {
        this->v_.set (::std::move (r));
        continue;
      }
    }

    // f
    //
    if (n.name () == "f" && n.namespace_ ().empty ())
    {
      ::std::unique_ptr< f_type > r (
        f_traits::create (i, f, this));

      if (!f_.present ())
      {
        this->f_.set (::std::move (r));
        continue;
      }
    }

    // old_f
    //
    if (n.name () == "old_f" && n.namespace_ ().empty ())
    {
      ::std::unique_ptr< old_f_type > r (
        old_f_traits::create (i, f, this));

      if (!old_f_.present ())
      {
        this->old_f_.set (::std::move (r));
        continue;
      }
    }

    // m
    //
    if (n.name () == "m" && n.namespace_ ().empty ())
    {
      ::std::unique_ptr< m_type > r (
        m_traits::create (i, f, this));

      if (!m_.present ())
      {
        this->m_.set (::std::move (r));
        continue;
      }
    }

    // epsilon
    //
    if (n.name () == "epsilon" && n.namespace_ ().empty ())
    {
      if (!epsilon_.present ())
      {
        this->epsilon_.set (epsilon_traits::create (i, f, this));
        continue;
      }
    }

    // sigma
    //
    if (n.name () == "sigma" && n.namespace_ ().empty ())
    {
      if (!sigma_.present ())
      {
        this->sigma_.set (sigma_traits::create (i, f, this));
        continue;
      }
    }

    // type
    //
    if (n.name () == "type" && n.namespace_ ().empty ())
    {
      ::std::unique_ptr< type_type > r (
        type_traits::create (i, f, this));

      if (!type_.present ())
      {
        this->type_.set (::std::move (r));
        continue;
      }
    }

    break;
  }

  if (!x_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "x",
      "");
  }

  if (!v_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "v",
      "");
  }

  if (!f_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "f",
      "");
  }

  if (!old_f_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "old_f",
      "");
  }

  if (!m_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "m",
      "");
  }

  if (!epsilon_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "epsilon",
      "");
  }

  if (!sigma_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "sigma",
      "");
  }

  if (!type_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "type",
      "");
  }
}

particle_t* particle_t::
_clone (::xml_schema::flags f,
        ::xml_schema::container* c) const
{
  return new class particle_t (*this, f, c);
}

particle_t& particle_t::
operator= (const particle_t& x)
{
  if (this != &x)
  {
    static_cast< ::xml_schema::type& > (*this) = x;
    this->x_ = x.x_;
    this->v_ = x.v_;
    this->f_ = x.f_;
    this->old_f_ = x.old_f_;
    this->m_ = x.m_;
    this->epsilon_ = x.epsilon_;
    this->sigma_ = x.sigma_;
    this->type_ = x.type_;
  }

  return *this;
}

particle_t::
~particle_t ()
{
}

// Checkpoint_t
//

Checkpoint_t::
Checkpoint_t ()
: ::xml_schema::type (),
  particle_ (this)
{
}

Checkpoint_t::
Checkpoint_t (const Checkpoint_t& x,
              ::xml_schema::flags f,
              ::xml_schema::container* c)
: ::xml_schema::type (x, f, c),
  particle_ (x.particle_, f, this)
{
}

Checkpoint_t::
Checkpoint_t (const ::xercesc::DOMElement& e,
              ::xml_schema::flags f,
              ::xml_schema::container* c)
: ::xml_schema::type (e, f | ::xml_schema::flags::base, c),
  particle_ (this)
{
  if ((f & ::xml_schema::flags::base) == 0)
  {
    ::xsd::cxx::xml::dom::parser< char > p (e, true, false, false);
    this->parse (p, f);
  }
}

void Checkpoint_t::
parse (::xsd::cxx::xml::dom::parser< char >& p,
       ::xml_schema::flags f)
{
  for (; p.more_content (); p.next_content (false))
  {
    const ::xercesc::DOMElement& i (p.cur_element ());
    const ::xsd::cxx::xml::qualified_name< char > n (
      ::xsd::cxx::xml::dom::name< char > (i));

    // particle
    //
    if (n.name () == "particle" && n.namespace_ ().empty ())
    {
      ::std::unique_ptr< particle_type > r (
        particle_traits::create (i, f, this));

      this->particle_.push_back (::std::move (r));
      continue;
    }

    break;
  }
}

Checkpoint_t* Checkpoint_t::
_clone (::xml_schema::flags f,
        ::xml_schema::container* c) const
{
  return new class Checkpoint_t (*this, f, c);
}

Checkpoint_t& Checkpoint_t::
operator= (const Checkpoint_t& x)
{
  if (this != &x)
  {
    static_cast< ::xml_schema::type& > (*this) = x;
    this->particle_ = x.particle_;
  }

  return *this;
}

Checkpoint_t::
~Checkpoint_t ()
{
}

#include <istream>
#include <xsd/cxx/xml/sax/std-input-source.hxx>
#include <xsd/cxx/tree/error-handler.hxx>

::std::unique_ptr< ::Checkpoint_t >
Checkpoint (const ::std::string& u,
            ::xml_schema::flags f,
            const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xsd::cxx::tree::error_handler< char > h;

  ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      u, h, p, f));

  h.throw_if_failed< ::xsd::cxx::tree::parsing< char > > ();

  return ::std::unique_ptr< ::Checkpoint_t > (
    ::Checkpoint (
      std::move (d), f | ::xml_schema::flags::own_dom, p));
}

::std::unique_ptr< ::Checkpoint_t >
Checkpoint (const ::std::string& u,
            ::xml_schema::error_handler& h,
            ::xml_schema::flags f,
            const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      u, h, p, f));

  if (!d.get ())
    throw ::xsd::cxx::tree::parsing< char > ();

  return ::std::unique_ptr< ::Checkpoint_t > (
    ::Checkpoint (
      std::move (d), f | ::xml_schema::flags::own_dom, p));
}

::std::unique_ptr< ::Checkpoint_t >
Checkpoint (const ::std::string& u,
            ::xercesc::DOMErrorHandler& h,
            ::xml_schema::flags f,
            const ::xml_schema::properties& p)
{
  ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      u, h, p, f));

  if (!d.get ())
    throw ::xsd::cxx::tree::parsing< char > ();

  return ::std::unique_ptr< ::Checkpoint_t > (
    ::Checkpoint (
      std::move (d), f | ::xml_schema::flags::own_dom, p));
}

::std::unique_ptr< ::Checkpoint_t >
Checkpoint (::std::istream& is,
            ::xml_schema::flags f,
            const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xsd::cxx::xml::sax::std_input_source isrc (is);
  return ::Checkpoint (isrc, f, p);
}

::std::unique_ptr< ::Checkpoint_t >
Checkpoint (::std::istream& is,
            ::xml_schema::error_handler& h,
            ::xml_schema::flags f,
            const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xsd::cxx::xml::sax::std_input_source isrc (is);
  return ::Checkpoint (isrc, h, f, p);
}

::std::unique_ptr< ::Checkpoint_t >
Checkpoint (::std::istream& is,
            ::xercesc::DOMErrorHandler& h,
            ::xml_schema::flags f,
            const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::sax::std_input_source isrc (is);
  return ::Checkpoint (isrc, h, f, p);
}

::std::unique_ptr< ::Checkpoint_t >
Checkpoint (::std::istream& is,
            const ::std::string& sid,
            ::xml_schema::flags f,
            const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xsd::cxx::xml::sax::std_input_source isrc (is, sid);
  return ::Checkpoint (isrc, f, p);
}

::std::unique_ptr< ::Checkpoint_t >
Checkpoint (::std::istream& is,
            const ::std::string& sid,
            ::xml_schema::error_handler& h,
            ::xml_schema::flags f,
            const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xsd::cxx::xml::sax::std_input_source isrc (is, sid);
  return ::Checkpoint (isrc, h, f, p);
}

::std::unique_ptr< ::Checkpoint_t >
Checkpoint (::std::istream& is,
            const ::std::string& sid,
            ::xercesc::DOMErrorHandler& h,
            ::xml_schema::flags f,
            const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::sax::std_input_source isrc (is, sid);
  return ::Checkpoint (isrc, h, f, p);
}

::std::unique_ptr< ::Checkpoint_t >
Checkpoint (::xercesc::InputSource& i,
            ::xml_schema::flags f,
            const ::xml_schema::properties& p)
{
  ::xsd::cxx::tree::error_handler< char > h;

  ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      i, h, p, f));

  h.throw_if_failed< ::xsd::cxx::tree::parsing< char > > ();

  return ::std::unique_ptr< ::Checkpoint_t > (
    ::Checkpoint (
      std::move (d), f | ::xml_schema::flags::own_dom, p));
}

::std::unique_ptr< ::Checkpoint_t >
Checkpoint (::xercesc::InputSource& i,
            ::xml_schema::error_handler& h,
            ::xml_schema::flags f,
            const ::xml_schema::properties& p)
{
  ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      i, h, p, f));

  if (!d.get ())
    throw ::xsd::cxx::tree::parsing< char > ();

  return ::std::unique_ptr< ::Checkpoint_t > (
    ::Checkpoint (
      std::move (d), f | ::xml_schema::flags::own_dom, p));
}

::std::unique_ptr< ::Checkpoint_t >
Checkpoint (::xercesc::InputSource& i,
            ::xercesc::DOMErrorHandler& h,
            ::xml_schema::flags f,
            const ::xml_schema::properties& p)
{
  ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      i, h, p, f));

  if (!d.get ())
    throw ::xsd::cxx::tree::parsing< char > ();

  return ::std::unique_ptr< ::Checkpoint_t > (
    ::Checkpoint (
      std::move (d), f | ::xml_schema::flags::own_dom, p));
}

::std::unique_ptr< ::Checkpoint_t >
Checkpoint (const ::xercesc::DOMDocument& doc,
            ::xml_schema::flags f,
            const ::xml_schema::properties& p)
{
  if (f & ::xml_schema::flags::keep_dom)
  {
    ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d (
      static_cast< ::xercesc::DOMDocument* > (doc.cloneNode (true)));

    return ::std::unique_ptr< ::Checkpoint_t > (
      ::Checkpoint (
        std::move (d), f | ::xml_schema::flags::own_dom, p));
  }

  const ::xercesc::DOMElement& e (*doc.getDocumentElement ());
  const ::xsd::cxx::xml::qualified_name< char > n (
    ::xsd::cxx::xml::dom::name< char > (e));

  if (n.name () == "Checkpoint" &&
      n.namespace_ () == "")
  {
    ::std::unique_ptr< ::Checkpoint_t > r (
      ::xsd::cxx::tree::traits< ::Checkpoint_t, char >::create (
        e, f, 0));
    return r;
  }

  throw ::xsd::cxx::tree::unexpected_element < char > (
    n.name (),
    n.namespace_ (),
    "Checkpoint",
    "");
}

::std::unique_ptr< ::Checkpoint_t >
Checkpoint (::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d,
            ::xml_schema::flags f,
            const ::xml_schema::properties&)
{
  ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > c (
    ((f & ::xml_schema::flags::keep_dom) &&
     !(f & ::xml_schema::flags::own_dom))
    ? static_cast< ::xercesc::DOMDocument* > (d->cloneNode (true))
    : 0);

  ::xercesc::DOMDocument& doc (c.get () ? *c : *d);
  const ::xercesc::DOMElement& e (*doc.getDocumentElement ());

  const ::xsd::cxx::xml::qualified_name< char > n (
    ::xsd::cxx::xml::dom::name< char > (e));

  if (f & ::xml_schema::flags::keep_dom)
    doc.setUserData (::xml_schema::dom::tree_node_key,
                     (c.get () ? &c : &d),
                     0);

  if (n.name () == "Checkpoint" &&
      n.namespace_ () == "")
  {
    ::std::unique_ptr< ::Checkpoint_t > r (
      ::xsd::cxx::tree::traits< ::Checkpoint_t, char >::create (
        e, f, 0));
    return r;
  }

  throw ::xsd::cxx::tree::unexpected_element < char > (
    n.name (),
    n.namespace_ (),
    "Checkpoint",
    "");
}

#include <ostream>
#include <xsd/cxx/tree/error-handler.hxx>
#include <xsd/cxx/xml/dom/serialization-source.hxx>

void
operator<< (::xercesc::DOMElement& e, const particle_t& i)
{
  e << static_cast< const ::xml_schema::type& > (i);

  // x
  //
  {
    ::xercesc::DOMElement& s (
      ::xsd::cxx::xml::dom::create_element (
        "x",
        e));

    s << i.x ();
  }

  // v
  //
  {
    ::xercesc::DOMElement& s (
      ::xsd::cxx::xml::dom::create_element (
        "v",
        e));

    s << i.v ();
  }

  // f
  //
  {
    ::xercesc::DOMElement& s (
      ::xsd::cxx::xml::dom::create_element (
        "f",
        e));

    s << i.f ();
  }

  // old_f
  //
  {
    ::xercesc::DOMElement& s (
      ::xsd::cxx::xml::dom::create_element (
        "old_f",
        e));

    s << i.old_f ();
  }

  // m
  //
  {
    ::xercesc::DOMElement& s (
      ::xsd::cxx::xml::dom::create_element (
        "m",
        e));

    s << i.m ();
  }

  // epsilon
  //
  {
    ::xercesc::DOMElement& s (
      ::xsd::cxx::xml::dom::create_element (
        "epsilon",
        e));

    s << ::xml_schema::as_double(i.epsilon ());
  }

  // sigma
  //
  {
    ::xercesc::DOMElement& s (
      ::xsd::cxx::xml::dom::create_element (
        "sigma",
        e));

    s << ::xml_schema::as_double(i.sigma ());
  }

  // type
  //
  {
    ::xercesc::DOMElement& s (
      ::xsd::cxx::xml::dom::create_element (
        "type",
        e));

    s << i.type ();
  }
}

void
operator<< (::xercesc::DOMElement& e, const Checkpoint_t& i)
{
  e << static_cast< const ::xml_schema::type& > (i);

  // particle
  //
  for (Checkpoint_t::particle_const_iterator
       b (i.particle ().begin ()), n (i.particle ().end ());
       b != n; ++b)
  {
    ::xercesc::DOMElement& s (
      ::xsd::cxx::xml::dom::create_element (
        "particle",
        e));

    s << *b;
  }
}

void
Checkpoint (::std::ostream& o,
            const ::Checkpoint_t& s,
            const ::xml_schema::namespace_infomap& m,
            const ::std::string& e,
            ::xml_schema::flags f)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0);

  ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d (
    ::Checkpoint (s, m, f));

  ::xsd::cxx::tree::error_handler< char > h;

  ::xsd::cxx::xml::dom::ostream_format_target t (o);
  if (!::xsd::cxx::xml::dom::serialize (t, *d, e, h, f))
  {
    h.throw_if_failed< ::xsd::cxx::tree::serialization< char > > ();
  }
}

void
Checkpoint (::std::ostream& o,
            const ::Checkpoint_t& s,
            ::xml_schema::error_handler& h,
            const ::xml_schema::namespace_infomap& m,
            const ::std::string& e,
            ::xml_schema::flags f)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0);

  ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d (
    ::Checkpoint (s, m, f));
  ::xsd::cxx::xml::dom::ostream_format_target t (o);
  if (!::xsd::cxx::xml::dom::serialize (t, *d, e, h, f))
  {
    throw ::xsd::cxx::tree::serialization< char > ();
  }
}

void
Checkpoint (::std::ostream& o,
            const ::Checkpoint_t& s,
            ::xercesc::DOMErrorHandler& h,
            const ::xml_schema::namespace_infomap& m,
            const ::std::string& e,
            ::xml_schema::flags f)
{
  ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d (
    ::Checkpoint (s, m, f));
  ::xsd::cxx::xml::dom::ostream_format_target t (o);
  if (!::xsd::cxx::xml::dom::serialize (t, *d, e, h, f))
  {
    throw ::xsd::cxx::tree::serialization< char > ();
  }
}

void
Checkpoint (::xercesc::XMLFormatTarget& t,
            const ::Checkpoint_t& s,
            const ::xml_schema::namespace_infomap& m,
            const ::std::string& e,
            ::xml_schema::flags f)
{
  ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d (
    ::Checkpoint (s, m, f));

  ::xsd::cxx::tree::error_handler< char > h;

  if (!::xsd::cxx::xml::dom::serialize (t, *d, e, h, f))
  {
    h.throw_if_failed< ::xsd::cxx::tree::serialization< char > > ();
  }
}

void
Checkpoint (::xercesc::XMLFormatTarget& t,
            const ::Checkpoint_t& s,
            ::xml_schema::error_handler& h,
            const ::xml_schema::namespace_infomap& m,
            const ::std::string& e,
            ::xml_schema::flags f)
{
  ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d (
    ::Checkpoint (s, m, f));
  if (!::xsd::cxx::xml::dom::serialize (t, *d, e, h, f))
  {
    throw ::xsd::cxx::tree::serialization< char > ();
  }
}

void
Checkpoint (::xercesc::XMLFormatTarget& t,
            const ::Checkpoint_t& s,
            ::xercesc::DOMErrorHandler& h,
            const ::xml_schema::namespace_infomap& m,
            const ::std::string& e,
            ::xml_schema::flags f)
{
  ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d (
    ::Checkpoint (s, m, f));
  if (!::xsd::cxx::xml::dom::serialize (t, *d, e, h, f))
  {
    throw ::xsd::cxx::tree::serialization< char > ();
  }
}

void
Checkpoint (::xercesc::DOMDocument& d,
            const ::Checkpoint_t& s,
            ::xml_schema::flags)
{
  ::xercesc::DOMElement& e (*d.getDocumentElement ());
  const ::xsd::cxx::xml::qualified_name< char > n (
    ::xsd::cxx::xml::dom::name< char > (e));

  if (n.name () == "Checkpoint" &&
      n.namespace_ () == "")
  {
    e << s;
  }
  else
  {
    throw ::xsd::cxx::tree::unexpected_element < char > (
      n.name (),
      n.namespace_ (),
      "Checkpoint",
      "");
  }
}

::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument >
Checkpoint (const ::Checkpoint_t& s,
            const ::xml_schema::namespace_infomap& m,
            ::xml_schema::flags f)
{
  ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::serialize< char > (
      "Checkpoint",
      "",
      m, f));

  ::Checkpoint (*d, s, f);
  return d;
}

#include <xsd/cxx/post.hxx>

// Begin epilogue.
//
//
// End epilogue.

