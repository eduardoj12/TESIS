#pragma once
#include <cstdarg>
namespace Eloquent {
    namespace ML {
        namespace Port {
            class DecisionTreeRegressorPH {
                public:
                    /**
                    * Predict class for features vector
                    */
                    float predict(float *x) {
                        if (x[8] <= 1230.5780029296875) {
                            if (x[11] <= 1245.5830078125) {
                                if (x[11] <= 525.2369995117188) {
                                    return 6.264349032115867f;
                                }

                                else {
                                    if (x[1] <= 774.2005004882812) {
                                        if (x[4] <= 116.41400146484375) {
                                            return 6.52964833654522f;
                                        }

                                        else {
                                            return 6.48164281748439f;
                                        }
                                    }

                                    else {
                                        return 6.618744779618183f;
                                    }
                                }
                            }

                            else {
                                if (x[1] <= 666.0755004882812) {
                                    if (x[3] <= 79.23300170898438) {
                                        return 6.644120607789916f;
                                    }

                                    else {
                                        return 6.564597386297031f;
                                    }
                                }

                                else {
                                    if (x[11] <= 1415.6199951171875) {
                                        return 6.6186049733843575f;
                                    }

                                    else {
                                        if (x[10] <= 1623.0264892578125) {
                                            return 6.704504284887921f;
                                        }

                                        else {
                                            return 6.6567261676920895f;
                                        }
                                    }
                                }
                            }
                        }

                        else {
                            if (x[1] <= 766.739990234375) {
                                if (x[3] <= 98.62699890136719) {
                                    return 6.495739229984458f;
                                }

                                else {
                                    if (x[7] <= 634.0429992675781) {
                                        if (x[1] <= 653.3519897460938) {
                                            return 6.162866694120335f;
                                        }

                                        else {
                                            return 6.142073489089302f;
                                        }
                                    }

                                    else {
                                        return 6.109362753606838f;
                                    }
                                }
                            }

                            else {
                                if (x[9] <= 3037.5455322265625) {
                                    if (x[6] <= 464.5885009765625) {
                                        return 6.3548421829215656f;
                                    }

                                    else {
                                        if (x[7] <= 530.8575134277344) {
                                            return 6.408455658639466f;
                                        }

                                        else {
                                            return 6.384215390853886f;
                                        }
                                    }
                                }

                                else {
                                    if (x[5] <= 146.1179962158203) {
                                        return 6.488523401265302f;
                                    }

                                    else {
                                        if (x[5] <= 196.0009994506836) {
                                            return 6.39556557241481f;
                                        }

                                        else {
                                            return 6.432076581121187f;
                                        }
                                    }
                                }
                            }
                        }
                    }

                protected:
                };
            }
        }
    }
