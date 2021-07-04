/*!
 *  @file KenoBet.hpp
 *  @brief KenoBet Class
 *
 *  Header of the KenoBet Class
 */

#ifndef KenoBet_hpp
#define KenoBet_hpp

#include <vector>

using number_type = int; //<! data type for a keno hit.
using cash_type = float; //<! Defines the wage type in this application.
using set_of_numbers_type = std::vector< number_type >;

class KenoBet {
    public:
        //! Creates an empty Keno bet.
        KenoBet( ) : m_wage(0)
        { /* empty */ };

        /*! Retrieves the player's wage on this bet.
            @return The wage value. */
        cash_type get_wage( void ) const;

        /*! Retrieves the Initial Credit.
            @return The Initial Credit. */
        float get_IC( void ) const;

        /*! Retrieves the Number of Rounds.
            @return The Number of Rounds. */
        int get_NR( void ) const;

        /*! Retrieves the final credit.
            @return n_FC The final credit. */
        float get_FC( void ) const;

        /*! Retrieves the Spent Cash.
            @return The Spent Cash. */
        float get_SC( void ) const;

        /*! Retrieves the Current Value.
            @return The Current Value. */
        float get_CurrentValue( void ) const;

        /*! Retrieves the Payout Value.
            @return The Payout Value. */
        float get_PayoffValue( void ) const;

        /*! Determine how many spots match the hits passed as argument.
            @param hits_ List of hits randomly chosen by the computer.
            @return An vector with the list of hits. */
        set_of_numbers_type get_hits( const set_of_numbers_type & hits_ ) const;

        /*! Return a vector< spot_type > with the spots the player has picked so far.
            @return The vector< spot_type > with the player's spots picked so far. */
        set_of_numbers_type get_spots( void ) const;


        /*! Sets the amount of money the player is betting.
            @param wage_ The wage.
            @return True if we have a wage above zero; false otherwise. */
        bool set_wage( cash_type wage_ );

        /*! Sets the initial credit.
            @param n_IC The initial credit. */
        void set_IC ( const float &n_IC );
        
        /*! Sets the number of rounds.
            @param n_NR The number of rounds. */
        void set_NR( const int &n_NR );

        /*! Sets the final credit.
            @param n_FC The final credit. */
        void set_FC( const float &n_FC );

        /*! Sets the spent cash.
            @param n_FC The spent cash. */
        void set_SC( const float &n_SC );

        /*! Sets the current value.
            @param CurrentValue The current value. */
        void set_CurrentValue( const float &CurrentValue );

        /*! Sets the payout value.
            @param PayoutValue The payout value. */
        void set_PayoffValue( const float &PayoffValue );

        /*! Adds a number to the spots only if the number is not already there.
            @param spot_ The number we wish to include in the bet.
            @return T if number chosen is successfully inserted; F otherwise. */
        bool add_number( number_type spot_ );

        //! Resets a bet to an empty state.
        void reset( void );

        /*! Returns to the current number of spots in the player's bet.
            @return Number of spots present in the bet. */
        size_t size( void ) const;

        /*! Fill vector with unique random numbers in range [1, 80]. */
        set_of_numbers_type generate_random(void) const;

        //! Print a payoff table
        void print_payofftable(std::vector<std::vector<float>> &payoff);

        /*! Print a vector
            @param vector The vector */
        void print_vector(set_of_numbers_type &vector, int size);

    private:
        cash_type   m_IC;             //<! Initial Credit.
        number_type m_NR;             //<! Number of Rounds.
        cash_type   m_FC = 0;         //<! Final Credit.
        cash_type   m_SC;             //<! Spent Cash.
        cash_type   m_PayoffValue;    //<! Payout Value. 
        cash_type   m_CurrentValue;   //<! Current Value.
        set_of_numbers_type m_spots;  //<! The player's bet.
        cash_type m_wage;             //<! The player's wage

};

#endif //KenoBet