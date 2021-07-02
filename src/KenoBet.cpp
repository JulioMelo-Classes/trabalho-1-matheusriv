/*!
 *  @file KenoBet.cpp
 *  @brief Source for KenoBet class
 *
 *  Source of the KenoBet class
 */

#include <iostream>
#include <algorithm>
#include <random>

#include "KenoBet.hpp"
#include "OtherFunctions.hpp"

    // Creates a KenoBet 
    KenoBet::KenoBet( void ) {
        this->m_spots.resize(0);
    }

    // Retrieves the player's wage on this bet.
    float KenoBet::get_wage(void) const {
        return this->m_wage;
    }

    // Determine how many spots match the hits passed as argument.
    set_of_numbers_type KenoBet::get_hits( const set_of_numbers_type & hits_ ) const {
        // Vector that will have the matched hits.
        set_of_numbers_type matches; 
        for(int i=0; i<20; i++){ 
            // Check if the hit element is one of the bet element.
            if(std::find(this->m_spots.begin(), this->m_spots.end(), hits_[i]) != this->m_spots.end()){ 
                // If true, append the element in the vector.
                matches.push_back(hits_[i]);
            }
        }
        // The return is the vector with the marched hits
        return matches;
    }

    // Return a vector< spot_type > with the spots the player has picked so far.
    set_of_numbers_type KenoBet::get_spots( void ) const {
        return this->m_spots;
    }


    // Sets the amount of money the player is betting.
    bool KenoBet::set_wage( cash_type wage_ ) {
        return (this->m_wage = wage_);
    }


    // Adds a number to the spots only if the number is not already there.
    bool KenoBet::add_number( number_type spot_ ) {
        if( !(std::find(this->m_spots.begin(), this->m_spots.end(), spot_) != this->m_spots.end()) && spot_ > 0 && spot_ <= 80 ){
            this->m_spots.push_back(spot_);
            quickSort(this->m_spots.data(), this->m_spots.size());
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

    // Returns a vector with 20 unique random numbers in range [1, 80].
    set_of_numbers_type KenoBet::generateRandom(void) const {
        // Create vector
        set_of_numbers_type vector_hits;
        // Fill the vector with 80 elements.
        for(int i=0; i<80; i++){  
            vector_hits.push_back(i+1);
        }
        // Create a real random number
        std::random_device r;
        // Shuffle vector content using the random number as seed
        std::shuffle(vector_hits.begin(), vector_hits.end(), std::default_random_engine(r()));
        // Resize vector to 20 elements
        vector_hits.resize(20);
        // Sort vector
        quickSort(vector_hits.data(), vector_hits.size());
        
        return vector_hits;
    }

