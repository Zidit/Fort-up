#ifndef RESOURCE_H_INCLUDED
#define RESOURCE_H_INCLUDED


#include <map>
#include <string>
#include <iostream>


template <class T> class ResourceManager
{
    private:
        typedef std::map <std::string,T*> ResourceMap;
        ResourceMap resources;

        T* get( std::string const & filename )
        {
            typename ResourceMap::iterator it = resources.find( filename );
            if ( it != resources.end( ) )
                return it->second;
            return NULL;
        }

    public:

        T* load(std::string const &filename)
        {
            T *res = get(filename);
            if (res)
                return res;

            res = new T(filename);

            if(!res)
            {
                std::cout << "Load failed: " << filename << std::endl;
                return NULL;
            }
            resources.insert( std::make_pair( filename, res) );
            return res;

        }

        void reload(std::string const &filename)
        {
            T* res = get(filename);
            if (res) res->reload();
        }

        void reloadAll()
        {
            typename ResourceMap::iterator it;
            for ( it = resources.begin( ); it != resources.end( ); ++it )
                it->second->reload();
        }


        void release(std::string const &filename)
        {
            typename ResourceMap::iterator it = resources.find( filename );
            if ( it != resources.end( ) )
            {
                delete it->second;
                resources.erase( it );
            }
        }

        ~ResourceManager( )
        {
            typename ResourceMap::iterator it;
            for ( it = resources.begin( ); it != resources.end( ); ++it )
                delete it->second;
        }
};




#endif // RESOURCE_H_INCLUDED
