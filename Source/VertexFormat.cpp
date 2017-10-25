#include "VertexFormat.h"

namespace Video
{

const VertexFormat VertexFormat::Position3TexCoord02Color4 = VertexFormat()
        .AddElement(Attribute::Position, 3)
        .AddElement(Attribute::TexCoord0, 2)
        .AddElement(Attribute::Color, 4);

const VertexFormat VertexFormat::Position3Normal3Color4 = VertexFormat()
        .AddElement(Attribute::Position, 3)
        .AddElement(Attribute::Normal, 3)
        .AddElement(Attribute::Color, 4);

const VertexFormat VertexFormat::Position3Normal3TexCoord02Color4 = VertexFormat()
        .AddElement(Attribute::Position, 3)
        .AddElement(Attribute::Normal, 3)
        .AddElement(Attribute::TexCoord0, 2)
        .AddElement(Attribute::Color, 4);

}
