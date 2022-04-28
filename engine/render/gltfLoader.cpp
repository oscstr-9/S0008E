#include "config.h"
#include "render/gltfLoader.h"
#include "core/VectorMath.h"
#define TINYGLTF_IMPLEMENTATION
//#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
// #define TINYGLTF_NOEXCEPTION // optional. disable exception handling.
#include "render/tiny_gltf.h"
#include <iostream>


using namespace tinygltf;

void LoadGLTF(std::string fileName, std::vector<gltfInfo>& info){

    std::vector<double> baseColor{1,1,1,1};

    Model model;
    TinyGLTF loader;

    std::string err;
    std::string warn;
    if(fileName.substr(fileName.find_last_of(".")+1) == "gltf"){
         bool ret = loader.LoadASCIIFromFile(&model, &err, &warn, "textures/GLTFs/" + fileName);
        if (!ret)
        {
            std::cout << "GLTF File could not be loaded." << std::endl << err << std::endl << warn << std::endl;
            return;
        }
    }
    else if(fileName.substr(fileName.find_last_of(".")+1) == "glb"){
        bool ret = loader.LoadBinaryFromFile(&model, &err, &warn, "textures/GLTFs/" + fileName);
        if (!ret)
        {
            std::cout << "GLB File could not be loaded." << std::endl << err << std::endl << warn << std::endl;
            return;
        }
    }
    else{
        std::cout << "incorrect file type" << std::endl;
        return;
    }

   
    
    int numOfMeshes = model.meshes.size();

    for (int i = 0; i < numOfMeshes; i++)
    {
        int numOfPrimitives = model.meshes[i].primitives.size();

        for (int j = 0; j < numOfPrimitives; j++)
        {
            
            // Buffers
            GLuint vertBuffer;
            GLuint indexBuffer;
            GLuint texture;
            GLuint normalMap;
            GLuint tangents;

            // Bind and prepare buffers
            glGenBuffers(1, &vertBuffer);    
            glBindBuffer(GL_ARRAY_BUFFER, vertBuffer);

            glGenBuffers(1, &indexBuffer);    
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

            // Accessors
            Accessor normalAccessor     = model.accessors[model.meshes[i].primitives[j].attributes["NORMAL"]];
            Accessor posAccessor        = model.accessors[model.meshes[i].primitives[j].attributes["POSITION"]];
            Accessor texAccessor        = model.accessors[model.meshes[i].primitives[j].attributes["TEXCOORD_0"]];
            Accessor tangentAccessor    = model.accessors[model.meshes[i].primitives[j].attributes["TANGENT"]];
            Accessor indices            = model.accessors[model.meshes[i].primitives[j].indices];

            // Normals
            int normalByteLength = model.bufferViews[normalAccessor.bufferView].byteLength;
            int normalByteOffset = model.bufferViews[normalAccessor.bufferView].byteOffset;
            int normalByteStride = model.bufferViews[normalAccessor.bufferView].byteStride;
            int normalBuffer     = model.bufferViews[normalAccessor.bufferView].buffer;

            // Positions
            int posByteLength = model.bufferViews[posAccessor.bufferView].byteLength;
            int posByteOffset = model.bufferViews[posAccessor.bufferView].byteOffset;
            int posByteStride = model.bufferViews[posAccessor.bufferView].byteStride;
            int posBuffer     = model.bufferViews[posAccessor.bufferView].buffer;

            // Texture coords
            int texByteLength = model.bufferViews[texAccessor.bufferView].byteLength;
            int texByteOffset = model.bufferViews[texAccessor.bufferView].byteOffset;
            int texByteStride = model.bufferViews[texAccessor.bufferView].byteStride;
            int texBuffer     = model.bufferViews[texAccessor.bufferView].buffer;

            // Tangents
            int tangentByteLength = model.bufferViews[tangentAccessor.bufferView].byteLength;
            int tangentByteOffset = model.bufferViews[tangentAccessor.bufferView].byteOffset;
            int tangentByteStride = model.bufferViews[tangentAccessor.bufferView].byteStride;
            int tangentBuffer     = model.bufferViews[tangentAccessor.bufferView].buffer;

            // Materials
            int materialBufferIndex = model.meshes[i].primitives[j].material;

            // Indices
            int indicesByteLength = model.bufferViews[indices.bufferView].byteLength;
            int indicesByteOffset = model.bufferViews[indices.bufferView].byteOffset;
            int indicesByteBuffer = model.bufferViews[indices.bufferView].buffer;
            int indexCount        = indices.count;

            
            // Texture
            int height;
            int width;
            int channels;
            unsigned char* img;
            auto colors = model.materials[materialBufferIndex].pbrMetallicRoughness.baseColorFactor;      
            auto baseColorTexture = model.materials[materialBufferIndex].pbrMetallicRoughness.baseColorTexture;
            if (baseColorTexture.index != -1){
                std::cout << "has texture" << std::endl;
                Image texImg = model.images[baseColorTexture.index];
                auto imgBuffer = model.bufferViews[texImg.bufferView];
                img = stbi_load_from_memory(model.buffers[imgBuffer.buffer].data.data() + imgBuffer.byteOffset, imgBuffer.byteLength, &width, &height, &channels, 0);

                if(img == NULL){
                    std::cout << stbi_failure_reason() << std::endl;
                }
            }
            else{
	            img = stbi_load("textures/default.png", &width, &height, &channels, 0);
                	if (img == NULL) {
                        std::cout << "Image loaded incorrectly" << std::endl;
	                }
            }

            // Load texture map into texture variable
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

            if (channels == 3)
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
            else if (channels == 4)
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);

            glGenerateMipmap(GL_TEXTURE_2D);

            glBindTexture(GL_TEXTURE_2D, 0);
            stbi_image_free(img);



            // NormalMapping
            auto nomalTexture = model.materials[materialBufferIndex].normalTexture;
            if (nomalTexture.index != -1){
                Image texImg = model.images[nomalTexture.index];
                auto imgBuffer = model.bufferViews[texImg.bufferView];
                img = stbi_load_from_memory(model.buffers[imgBuffer.buffer].data.data() + imgBuffer.byteOffset, imgBuffer.byteLength, &width, &height, &channels, 0);

                if(img == NULL){
                    std::cout << stbi_failure_reason() << std::endl;
                }
                else{
                    // Load normal map into nomalMap variable
                    glGenTextures(1, &normalMap);
                    glBindTexture(GL_TEXTURE_2D, normalMap);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

                    if (channels == 3)
                        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
                    else if (channels == 4)
                        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);

                    glGenerateMipmap(GL_TEXTURE_2D);

                    glBindTexture(GL_TEXTURE_2D, 0);
                    stbi_image_free(img);
                }
            }
            else{
                std::cout << "No normal map found" << std::endl;
            }

            

            // Bind the correct normal map
            
            // Bind texture to gpu with syntax below, example in textureResource. add texture gluint to GLTFinfo struct for easy access in render function.

	        glBufferData(GL_ARRAY_BUFFER, posByteLength+normalByteLength+texByteLength+tangentByteLength, NULL, GL_STATIC_DRAW);
            glBufferSubData(GL_ARRAY_BUFFER, 0, posByteLength, (void*)(model.buffers[posBuffer].data.data()+posByteOffset+posAccessor.byteOffset));
	        glBufferSubData(GL_ARRAY_BUFFER, posByteLength, texByteLength, (void*)(model.buffers[texBuffer].data.data()+texByteOffset+texAccessor.byteOffset));
	        glBufferSubData(GL_ARRAY_BUFFER, posByteLength+texByteLength, normalByteLength, (void*)(model.buffers[normalBuffer].data.data()+normalByteOffset+normalAccessor.byteOffset));
	        glBufferSubData(GL_ARRAY_BUFFER, posByteLength+texByteLength+normalByteLength, tangentByteLength, (void*)(model.buffers[tangentBuffer].data.data()+tangentByteOffset+tangentAccessor.byteOffset));

	        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesByteLength, (void*)(model.buffers[indicesByteBuffer].data.data()+indicesByteOffset+indices.byteOffset), GL_STATIC_DRAW);

            info.push_back(gltfInfo{
                           vertBuffer, 
                           indexBuffer,
                           texture,
                           normalMap,
                           VectorMath4{colors[0],colors[1],colors[2],colors[3]},
                           model.accessors[model.meshes[i].primitives[j].indices].componentType,
                           posByteStride,
                           posByteLength,
                           texByteStride,
                           texByteLength,
                           normalByteStride,
                           normalByteLength,
                           indexCount,
                           tangentByteStride,
                           tangentByteLength});
        }
    }
} 

void RenderGLTF(std::vector<gltfInfo>& info, std::shared_ptr <ShaderResource> shaders){
    
    // Itterates through all meshes and all primitives in each mesh to render the model
    for(int i = 0; i < info.size(); i++)
    {
        shaders->setSampler(0, "textureArray");
        shaders->setSampler(1, "normalArray");

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, info[i].texture);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, info[i].normalMap);

        glBindBuffer(GL_ARRAY_BUFFER, info[i].vertBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, info[i].indexBuffer);

        shaders->setVec4(info[i].color, "colorInput");

        // Render
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(2);
        glEnableVertexAttribArray(3);
        glEnableVertexAttribArray(4);
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, info[i].posByteStride, NULL);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, info[i].texByteStride, (GLvoid*)info[i].posByteLength);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, info[i].normalByteStride, (GLvoid*)(info[i].posByteLength+info[i].texByteLength));
        glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, info[i].tangentByteStride, (GLvoid*)(info[i].posByteLength+info[i].texByteLength+info[i].normalByteLength));
        
        glDrawElements(GL_TRIANGLES, info[i].indexCount, info[i].componentType, 0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

}