#pragma once
#include <cstdarg>
namespace Eloquent {
    namespace ML {
        namespace Port {
            class DecisionTreeRegressor {
                public:
                    /**
                    * Predict class for features vector
                    */
                    float predict(float *x) {
                        if (x[8] <= 1100.3375244140625) {
                            if (x[6] <= 671.8280029296875) {
                                if (x[1] <= 408.6899871826172) {
                                    return 58.69576791687097f;
                                }

                                else {
                                    if (x[3] <= 162.4029998779297) {
                                        if (x[5] <= 84.56100082397461) {
                                            return 49.539571366668326f;
                                        }

                                        else {
                                            return 51.682245551950814f;
                                        }
                                    }

                                    else {
                                        return 45.245894641354255f;
                                    }
                                }
                            }

                            else {
                                if (x[0] <= 3817.1585693359375) {
                                    if (x[11] <= 1806.833984375) {
                                        if (x[10] <= 1667.5394897460938) {
                                            return 45.255671780251525f;
                                        }

                                        else {
                                            return 45.20168686461478f;
                                        }
                                    }

                                    else {
                                        return 45.32388928553897f;
                                    }
                                }

                                else {
                                    return 45.42975636745506f;
                                }
                            }
                        }

                        else {
                            if (x[1] <= 766.739990234375) {
                                if (x[3] <= 98.62699890136719) {
                                    if (x[2] <= 175.7760009765625) {
                                        return 54.34336436623298f;
                                    }

                                    else {
                                        return 52.32065618516317f;
                                    }
                                }

                                else {
                                    if (x[11] <= 1181.196533203125) {
                                        if (x[11] <= 1009.2875061035156) {
                                            return 62.77003058184077f;
                                        }

                                        else {
                                            return 62.87228015587404f;
                                        }
                                    }

                                    else {
                                        return 62.97219563166729f;
                                    }
                                }
                            }

                            else {
                                if (x[8] <= 1365.8179931640625) {
                                    return 53.36787443532157f;
                                }

                                else {
                                    if (x[3] <= 140.1490020751953) {
                                        if (x[3] <= 137.74649810791016) {
                                            return 55.08460161056193f;
                                        }

                                        else {
                                            return 55.24359832327836f;
                                        }
                                    }

                                    else {
                                        if (x[1] <= 884.3695068359375) {
                                            return 55.14603825160635f;
                                        }

                                        else {
                                            return 54.625234472362195f;
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
