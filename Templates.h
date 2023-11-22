#ifndef TEMPLATES_H
#define TEMPLATES_H

template <class T> void double_new(T**& v,int x,int y)
{
    v=new T*[x];
    for(int i=0;i<x;i++)
    {
        v[i]=new T[y];
        for(int j=0;j<y;j++)
        {
            v[i][j]=0;
        }
    }
}
template <class T> void multi_new(T*** &v,int x,int y,int z)
{
    v=new T**[x];
    for(int i=0;i<x;i++)
    {
        v[i]=new T*[y];
        for(int j=0;j<y;j++)
        {
            v[i][j]=new T[z];
            for(int k=0;k<z;k++)
            {
                v[i][j][k]=0;
            }
        }
    }
}
template <class T> bool all_equal(T* &v,int x)
{
    for(int i=0;i<x;i++)
    {
        if(v[i]!=x)
            return false;
    }
    return true;
}
template <class T> T arraysum(T* &v,int x)
{
    T thesum=0;
    for(int i=0;i<x;i++)
    {
        thesum+=v[i];
    }
    return thesum;
}
template <class T> T arraysum(T** &v,int x,int y)
{
    T thesum=0;
    for(int i=0;i<x;i++)
    {
        thesum+=arraysum(v[i],y);
    }
    return thesum;
}
#endif // TEMPLATES_H
