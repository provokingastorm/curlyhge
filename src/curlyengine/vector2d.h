#ifndef Vector2D_H_
#define Vector2D_H_


// ----------------------------------------------------------------------------
// Vector2D - Declaration
// ----------------------------------------------------------------------------

struct Vector2D
{
    float X;
    float Y;

    Vector2D(float InX = 0.0f, float InY = 0.0f)
        :   X(InX)
        ,   Y(InY) 
    {
    }

    Vector2D( const Vector2D & InVector2D )
    {
        X = InVector2D.X;
        Y = InVector2D.Y;
    }

    Vector2D& operator=( const Vector2D & InVector2D )
    {
        X = InVector2D.X;
        Y = InVector2D.Y;
        return *this;
    }

    inline bool operator== ( const Vector2D & InVector2D ) const
    {
        return ( X == InVector2D.X && Y == InVector2D.Y );
    }

    inline bool operator!= ( const Vector2D & InVector2D ) const
    {
        return ( X != InVector2D.X && Y != InVector2D.Y );
    }

    inline static Vector2D& Zero()
    {
        static Vector2D ZeroVector2D(0.0f, 0.0f);
        return ZeroVector2D;
    }

    inline Vector2D operator+ ( const Vector2D & InVector2D ) const
    {
          Vector2D NewVector2D;
          NewVector2D.X = X + InVector2D.X;
          NewVector2D.Y = Y + InVector2D.Y;
          return NewVector2D;
    }

    inline Vector2D operator- ( const Vector2D & InVector2D ) const
    {
          Vector2D NewVector2D;
          NewVector2D.X = X - InVector2D.X;
          NewVector2D.Y = Y - InVector2D.Y;
          return NewVector2D;
    }

    inline Vector2D operator* ( const Vector2D & InVector2D ) const
    {
          Vector2D NewVector2D;
          NewVector2D.X = X * InVector2D.X;
          NewVector2D.Y = Y * InVector2D.Y;
          return NewVector2D;
    }

    inline Vector2D operator/ ( const Vector2D & InVector2D ) const
    {
          Vector2D NewVector2D;
          NewVector2D.X = X / InVector2D.X;
          NewVector2D.Y = Y / InVector2D.Y;
          return NewVector2D;
    }

	inline Vector2D& operator+= ( Vector2D & InVector2D )
    {
        X += InVector2D.X;
        Y += InVector2D.Y;
        return *this;
    }

	inline Vector2D& operator-= ( Vector2D & InVector2D )
    {
        X -= InVector2D.X;
        Y -= InVector2D.Y;
        return *this;
    }

	inline Vector2D& operator*= ( Vector2D & InVector2D )
    {
        X *= InVector2D.X;
        Y *= InVector2D.Y;
        return *this;
    }

	inline Vector2D& operator/= ( Vector2D & InVector2D )
    {
        X /= InVector2D.X;
        Y /= InVector2D.Y;
        return *this;
    }

	inline Vector2D& operator+= ( float Scalar )
    {
        X += Scalar;
        Y += Scalar;
        return *this;
    }

	inline Vector2D& operator-= ( float Scalar )
    {
        X -= Scalar;
        Y -= Scalar;
        return *this;
    } 

	inline Vector2D& operator*= ( float Scalar )
    {
        X *= Scalar;
        Y *= Scalar;
        return *this;
    } 

	inline Vector2D& operator/= ( float Scalar )
    {
        X /= Scalar;
        Y /= Scalar;
        return *this;
    } 

    inline friend Vector2D operator- ( const Vector2D & InVector2D )
    {
        return Vector2D(-InVector2D.X, -InVector2D.Y);
    }

};

#endif

// EOF
