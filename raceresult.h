/**
 *  Results.h
 *
 *  PHP results class to retrieve the results from a job
 *
 *  @author Aljar Meesters <aljar.meesters@copernica.com>
 *  @copyright 2015 Copernica BV
 */


/**
 *  include guard
 */
#pragma once


/**
 *  Dependencies
 */
#include "stats.h"
#include "winner.h"

/**
 *  Class definition
 */
class RaceResult : public Php::Base
{
protected:
    /**
     *  JSON object holding all properties
     *  @var JSON::Object
     */
    JSON::Object _json;

public:
    /**
     *  Constructor
     *  @param  output
     */
    RaceResult(const JSON::Object &output) : _json(output) {}

    /**
     *  Destructor
     */
    virtual ~RaceResult() = default;

    /**
     *  Get the time when the job is started
     *  @return Php::Value
     */
    Php::Value started() const
    {
        return _json.decimal("started");
    }

    /**
     *  Get the time when the job is finished
     *  @return Php::Value
     */
    Php::Value finished() const
    {
        return _json.decimal("finished");
    }

    /**
     *  Get the total runtime
     *  @return Php::Value
     */
    Php::Value runtime() const
    {
        return _json.decimal("runtime");
    }

    /**
     *  Get the number of processes during the race
     *  @return Php::Value
     */
    Php::Value processes() const
    {
        return _json.integer("processes");
    }

    /**
     *  Get the result, only used for races and regular jobs
     *  @return Php::Value
     */
    Php::Value result() const
    {
        // unserialize the base64 encoded object from stdout
        return Php::call("unserialize", Php::call("base64_decode", _json.object("winner").c_str("stdout")));
    }

    /**
     *  Get the winner class with all winner statistics
     *  @return Php::Value
     */
    Php::Value winner()
    {
        return Php::Object("Yothalot\\Winner", new Winner(_json.object("winner")));
    }
};

