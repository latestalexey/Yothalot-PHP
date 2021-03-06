/**
 *  Input.h
 * 
 *  Utility class for reading files that were created by the Yothalot\Output class
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
#include "inputiterator.h"
#include <phpcpp.h>

/**
 *  Class definition
 */
class Input : public Php::Base, public Php::Traversable
{
private:
    /**
     *  The name
     *  @var std::string
     */
    std::string _name;

    /**
     *  The input object that is used if the next() method is called
     *  @var std::shared_ptr<Yothalot::Input>
     */
    std::shared_ptr<Yothalot::Input> _input;

public:
    /**
     *  The PHP constructor
     *  @param  params
     */
    void __construct(Php::Parameters &params)
    {
        // check params
        if (params.size() < 1) Php::error << "No filename passed to Yothalot\\Input constructor" << std::flush;

        // copy the name
        _name = params[0].stringValue();
    }

    /**
     *  Retrieve the full file name
     *  @return Php::Value
     */
    Php::Value name() const
    {
        // return member
        return _name;
    }

    /**
     *  File size
     *  @return Php::Value
     */
    Php::Value size() const
    {
        // prevent exceptions
        try
        {
            // create impl object
            return (int64_t) Yothalot::Input(_name.data()).size();
        }
        catch (const std::runtime_error &exception)
        {
            // failed to open input object
            return 0;
        }
    }

    /**
     *  Is the input file a valid yothalot file
     *  @return Php::Value
     */
    Php::Value valid()
    {
        // prevent exceptions
        try
        {
            // create impl object
            return (bool) Yothalot::Input(_name.data()).valid();
        }
        catch (const std::runtime_error &exception)
        {
            // if we end up here we clearly are not valid
            return false;
        }
    }

    /**
     *  Retrieve an instance of the iterator
     *  @return Php::Iterator
     */
    virtual Php::Iterator *getIterator() override
    {
        // construct the new iterator
        return new InputIterator(this, _name);
    }

    /**
     *  Get the next record
     *  @return Php::Value
     */
    Php::Value next()
    {
        // prevent exceptions
        try
        {
            // do we already have an input object?
            if (_input == nullptr) _input = std::make_shared<Yothalot::Input>(_name.data());

            // object must be valid
            if (!_input->valid()) return nullptr;

            // construct a yothalot record
            auto record = std::make_shared<Yothalot::Record>(*_input);

            // return object
            return Php::Object("Yothalot\\Record", new Record(record));
        }
        catch (...)
        {
            // object is in an invalid state
            return nullptr;
        }
    }
    
    /**
     *  Seek records
     *  @param  params
     *  @return Php::Value
     */
    Php::Value seek(Php::Parameters &params)
    {
        // prevent exceptions
        try
        {
            // do we already have an input object?
            if (_input == nullptr) _input = std::make_shared<Yothalot::Input>(_name.data());

            // object must be valid
            if (!_input->valid()) return 0;

            // was a parameter passed?
            if (params.size() == 0)
            {
                // seek to the end
                return (int)_input->seek();
            }
            else
            {
                // get the seek value
                int value = params[0];
                
                // seek passed number of items
                return (int)_input->seek(value);
            }
        }
        catch (...)
        {
            // object is in an invalid state
            return 0;
        }
    }
};

