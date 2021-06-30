/*!
 *  @file KenoBet.cpp
 *  @brief Source for KenoBet class
 *
 *  Source with the KenoBet class
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <random>

#include "KenoBet.hpp"

    /* 
      ----------------------------------------------------------
        Get
      ----------------------------------------------------------
    */ 

    // Retrieves the player's wage on this bet.
    float KenoBet::get_wage(void) const 
    {
        return this->m_wage;
    }

    // Determine how many spots match the hits passed as argument.
    set_of_numbers_type KenoBet::get_hits( const set_of_numbers_type & hits_ ) const 
    {
        set_of_numbers_type matches; // vector with the matched hits
        for(int i=0; i<20; i++){ 
            // if the hit element is one of the bet element.
            if(in_array(hits_[i], this->m_spots.data(), this->m_spots.size())){ 
                matches.push_back(hits_[i]);
            }
        }
        return matches; // Return vector with the marched hits
    }

    // Return a vector< spot_type > with the spots the player has picked so far.
    set_of_numbers_type KenoBet::get_spots( void ) const 
    {
        return this->m_spots;
    }


    /* 
      ----------------------------------------------------------
      Set 
      ----------------------------------------------------------
    */

    // Sets the amount of money the player is betting.
    bool KenoBet::set_wage( cash_type wage_ )
    {
        return (this->m_wage = wage_);
    }


    /* 
      ----------------------------------------------------------
        Methods 
      ----------------------------------------------------------
    */

    // Adds a number to the spots only if the number is not already there.
    bool KenoBet::add_number( number_type spot_ ) 
    {
        if( !in_array(spot_, this->m_spots.data(), this->m_spots.size()) 
            && this->m_spots.size() < this->m_maxSpots && spot_ > 0 
            && spot_ <= 80 ){
                this->m_spots.push_back(spot_);
                quick_sort(this->m_spots.data(), this->m_spots.size());
                return true;
            }
        return false;
    }

    // Resets a bet to an empty state.
    void KenoBet::reset( void ) {
        m_spots.clear();
        m_spots.resize(0);
    }

    // Returns to the current number of spots in the player's bet.
    size_t KenoBet::size( void ) const {
        return m_spots.size();
    }

