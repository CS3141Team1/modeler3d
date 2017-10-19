#include "VertexFormat.h"

namespace Video
{

const VertexFormat VertexFormat::Position3fTexCoord02fColor4f = VertexFormat()
        .AddElement(Attribute::Position, 3)
        .AddElement(Attribute::TexCoord0, 2)
        .AddElement(Attribute::Color, 4);

const VertexFormat VertexFormat::Position3fNormal3fColor4f = VertexFormat()
        .AddElement(Attribute::Position, 3)
        .AddElement(Attribute::Normal, 3)
        .AddElement(Attribute::Color, 4);

const VertexFormat VertexFormat::Position3fNormal3fTexCoord02fColor4f = VertexFormat()
        .AddElement(Attribute::Position, 3)
        .AddElement(Attribute::Normal, 3)
        .AddElement(Attribute::TexCoord0, 2)
        .AddElement(Attribute::Color, 4);

}
