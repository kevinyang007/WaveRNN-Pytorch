#ifndef NET_IMPL_H
#define NET_IMPL_H

#include <stdio.h>
#include <vector>
#include "wavernn.h"

const int RES_BLOCKS = 3;
const int UPSAMPLE_LAYERS = 3;

class ResBlock{
    std::vector<TorchLayer> resblock;
public:
    ResBlock() = default;
    void loadNext( FILE* fd );
    Matrixf apply( const Matrixf& x );
};

class Resnet{
    TorchLayer conv_in;
    TorchLayer batch_norm;
    ResBlock resblock;
    TorchLayer conv_out;
    TorchLayer stretch2d;  //moved stretch2d layer into resnet from upsample as in python code

public:
    Resnet() = default;
    void loadNext( FILE* fd );
    Matrixf apply( const Matrixf& x );
};

class UpsampleNetwork{
    std::vector<TorchLayer> up_layers;

public:
    UpsampleNetwork() = default;
    void loadNext( FILE* fd );
    Matrixf apply( const Matrixf& x );
};

class Model{
    UpsampleNetwork upsample;
    Resnet resnet;
    TorchLayer I;
    TorchLayer rnn1;
    TorchLayer fc1;
    TorchLayer fc2;

public:
    Model() = default;
    void loadNext( FILE* fd );
    Vectorf apply( const Matrixf& x );
};


#endif // NET_IMPL_H
