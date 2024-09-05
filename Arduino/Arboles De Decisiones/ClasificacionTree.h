#pragma once
#include <cstdarg>
namespace Eloquent {
    namespace ML {
        namespace Port {
            class ClasificacionTree {
                public:
                    /**
                    * Predict class for features vector
                    */
                    int predict(float *x) {
                        if (x[8] <= -0.23128797113895416) {
                            if (x[1] <= -1.2261440753936768) {
                                return 1;
                            }

                            else {
                                return 0;
                            }
                        }

                        else {
                            if (x[7] <= 0.2584883123636246) {
                                if (x[3] <= 0.26049094647169113) {
                                    if (x[2] <= -0.6328769028186798) {
                                        return 1;
                                    }

                                    else {
                                        if (x[0] <= 0.32712942361831665) {
                                            return 0;
                                        }

                                        else {
                                            return 1;
                                        }
                                    }
                                }

                                else {
                                    return 0;
                                }
                            }

                            else {
                                return 1;
                            }
                        }
                    }

                protected:
                };
            }
        }
    }
