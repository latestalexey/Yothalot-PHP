/**
 *  Serialized.h
 *
 *  Object that takes care of serializing and unserializing a job
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2015 Copernica BV
 */

/**
 *  Include guard
 */
#pragma once

/**
 *  Dependencies
 */
#include "json/object.h"
#include "jobimpl.h"

/**
 *  Class definition
 */
class Serialized : public JSON::Object
{
public:
    /**
     *  Constructor to serialize
     *  @param  impl        Job implementation object that is going to be serialized
     */
    Serialized(JobImpl *impl)
    {
        // one member holds all job data
        set("job", impl->json());

        // freeze the job, from now on no more data may be added
        impl->freeze();
    }

    /**
     *  Constructor to unserialize
     *  @param  buffer
     *  @param  size
     */
    Serialized(const char *buffer, size_t size) : 
        JSON::Object(buffer, size) {}

    /**
     *  Destructor
     */
    virtual ~Serialized() {}
};

