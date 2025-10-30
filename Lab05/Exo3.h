#ifndef QUADRATIC_PROBING_H
#define QUADRATIC_PROBING_H

#include <vector>
#include <algorithm>
#include <functional>
#include <string>
using namespace std;

int nextPrime( int n );

// QuadraticProbing Hash table class
//
// CONSTRUCTION: an approximate initial size or default of 101
//
// ******************PUBLIC OPERATIONS*********************
// bool insert( x )       --> Insert x
// bool remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// void makeEmpty( )      --> Remove all items
// int hashCode( string str ) --> Global method to hash strings

template <typename HashedObj>
class HashTable
{
  public:
    explicit HashTable( int size = 101 ) : array( nextPrime( size ) )
      { makeEmpty( ); }

    bool contains( const HashedObj & x ) const
    {
        return isActive( findPos( x ) );
    }

    void makeEmpty( )
    {
        currentSize = 0;
        for( auto & entry : array )
            entry.info = EMPTY;
    }

    bool insert( const HashedObj & x )
    {
        // Insert x as active
        int currentPos = findPos( x );
        if( isActive( currentPos ) )
            return false;

        if( array[ currentPos ].info != DELETED )
            ++currentSize;

        array[ currentPos ].element = x;
        array[ currentPos ].info = ACTIVE;

        // Rehash; see Section 5.5
        if( currentSize > array.size( ) / 2 )
            rehash( );

        return true;
    }
    
    bool insert( HashedObj && x )
    {
        // Insert x as active
        int currentPos = findPos( x );
        if( isActive( currentPos ) )
            return false;

        if( array[ currentPos ].info != DELETED )
            ++currentSize;

        array[ currentPos ] = std::move( x );
        array[ currentPos ].info = ACTIVE;

        // Rehash; see Section 5.5
        if( currentSize > array.size( ) / 2 )
            rehash( );

        return true;
    }

    bool remove( const HashedObj & x )
    {
        int currentPos = findPos( x );
        if( !isActive( currentPos ) )
            return false;

        array[ currentPos ].info = DELETED;
        return true;
    }

    enum EntryType { ACTIVE, EMPTY, DELETED };

  private:
    struct HashEntry
    {
        HashedObj element;
        EntryType info;

        HashEntry( const HashedObj & e = HashedObj{ }, EntryType i = EMPTY )
          : element{ e }, info{ i } { }
        
        HashEntry( HashedObj && e, EntryType i = EMPTY )
          : element{ std::move( e ) }, info{ i } { }
    };
    
    vector<HashEntry> array;
    int currentSize;

    bool isActive( int currentPos ) const
    { 
		return array[ currentPos ].info == ACTIVE; 
	}

    // Linear Prob
    int findPos(const HashedObj& x) const
    {
        int currentPos = myhash(x);
        int n = array.size();
        // we are always sure that we can find a place since in the insert function we check if the new size > size / 2
        while(array[currentPos].info != EMPTY && array[currentPos].element != x)
        {
            currentPos = (currentPos+1)%n;  // Linear probing
        }
        return currentPos;
    }

    // Double Hashing
    int hash2 (const HashedObj & x) const {
        int n = nextPrime(array.size()/2);
        return (n - myhash(x))%n;
    }
    int findPos2 (const HashedObj & x) const 
    {
        int currentPos = myhash(x);
        // int position = myhash(x)
        int n = array.size();
        while (array[currentPos].info != EMPTY && array[currentPos].element != x) {
            currentPos = (currentPos + hash2(x)) % n;
        }
        // while .... {
        //   currentPos = position + i*(hash2(x))
        //   i++ 
        // }
        return currentPos;
    }

    void rehash( )
    {
        vector<HashEntry> oldArray = array;

        // Create new double-sized, empty table
        array.resize( nextPrime( 2 * oldArray.size( ) ) );
        for( auto & entry : array )
            entry.info = EMPTY;

        // Copy table over
        currentSize = 0;
        for( auto & entry : oldArray )
            if( entry.info == ACTIVE )
                insert( std::move( entry.element ) );
    }

    size_t myhash( const HashedObj & x ) const
    {
        static hash<HashedObj> hf;
        return hf( x ) % array.size( );
    }
};

#endif

// 1-Array of Hash Entries: A vector of HashEntry objects, where each entry contains the element and its state
// (ACTIVE, EMPTY, DELETED)

// 2-Insert: The element is placed at the computed position, marking it as ACTIVE. 
// If the position is already occupied, quadratic probing is used to find the next available position.
// Delete: The element is marked as DELETED in the hash table.

// 3-Collision Handling:
// Quadratic Probing: When a collision occurs, quadratic probing is used to find the next available position 
// by incrementally increasing the offset (1, 4, 9, 16, ...).
