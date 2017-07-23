Rgb getColorFLT( float colorPoly, int rgb, int n, int maxiter ) {
    switch ( rgb ) {
        case 1:
            return getRgbFromTable( n, maxiter );
        case 2:
            return getRgbSmooth( n, maxiter );
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            return getRgbSmoothCPFLT( colorPoly, n, maxiter );
        case 9:
            return getRgb2( n, maxiter );
        case 10:
            return getRgb3( n, maxiter );
        case 11:
            return getRgb4( n, maxiter );
        case 12:
            return getRgb5( n, maxiter );
        case 13:
            return getRgbSmoothCPFLT( colorPoly, n, maxiter );
        default:
            return getRgb( n, maxiter );
        }
}

Rgb getColorDBL( double colorPoly, int rgb, int n, int maxiter ) {
    switch ( rgb ) {
        case 1:
            return getRgbFromTable( n, maxiter );
        case 2:
            return getRgbSmooth( n, maxiter );
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            return getRgbSmoothCPDBL( colorPoly, n, maxiter );
        case 9:
            return getRgb2( n, maxiter );
        case 10:
            return getRgb3( n, maxiter );
        case 11:
            return getRgb4( n, maxiter );
        case 12:
            return getRgb5( n, maxiter );
        case 13:
            return getRgbSmoothCPDBL( colorPoly, n, maxiter );
        default:
            return getRgb( n, maxiter );
        }
}

Rgb getColorLDBL( long double colorPoly, int rgb, int n, int maxiter ) {
    switch ( rgb ) {
        case 1:
            return getRgbFromTable( n, maxiter );
        case 2:
            return getRgbSmooth( n, maxiter );
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            return getRgbSmoothCPLDBL( colorPoly, n, maxiter );
        case 9:
            return getRgb2( n, maxiter );
        case 10:
            return getRgb3( n, maxiter );
        case 11:
            return getRgb4( n, maxiter );
        case 12:
            return getRgb5( n, maxiter );
        case 13:
            return getRgbSmoothCPLDBL( colorPoly, n, maxiter );
        default:
            return getRgb( n, maxiter );
        }
}

Rgb getColor128( __float128 colorPoly, int rgb, int n, int maxiter ) {
    switch ( rgb ) {
        case 1:
            return getRgbFromTable( n, maxiter );
        case 2:
            return getRgbSmooth( n, maxiter );
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            return getRgbSmoothCP128( colorPoly, n, maxiter );
        case 9:
            return getRgb2( n, maxiter );
        case 10:
            return getRgb3( n, maxiter );
        case 11:
            return getRgb4( n, maxiter );
        case 12:
            return getRgb5( n, maxiter );
        case 13:
            return getRgbSmoothCP128( colorPoly, n, maxiter );
        default:
            return getRgb( n, maxiter );
    }
}

