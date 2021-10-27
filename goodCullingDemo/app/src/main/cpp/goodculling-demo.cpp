/*
 * Copyright 2021 Huawei Technologies Co., Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdlib.h>
#include <vector>
#include <jni.h>
#include <android/log.h>
#include "include/GoodCulling.h"

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "GoodCulling", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "GoodCulling", __VA_ARGS__))
#define LOGD(...) ((void)__android_log_print(ANDROID_LOG_DEBUG, "GoodCulling", __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "GoodCulling", __VA_ARGS__))

using MeshData = OccluderData;

struct Vec3 {
    Vec3() {}
    Vec3(float x1, float y1, float z1) : x(x1), y(y1), z(z1) {}
    ~Vec3() {}

    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
};

struct Object {
    int id = 0;
    int meshId = 0;
    MeshData meshData;
    Vec3 minBox;
    Vec3 maxBox;
    bool updateTranFlag = true;
    std::vector<float> transformMatrix;
    Vec3 position;
    Vec3 rotation;
    Vec3 scale;
};

const unsigned int VERTEX_DIMENSION_CNT = 3;  // every vertex include x y z
std::vector<Object> senceObjArray;

float* GetBoundingBox(Vec3 box)
{
    std::vector<float> result = {box.x, box.y, box.z};
    return &result[0];
}

void CreateSence(std::vector<Object>& senceObjArray)
{
    Object object_0;
    Object object_1;
    Object object_2;
    Object object_3;

    // prepare mesh data
    MeshData meshData;
    // prepare vertex data of mesh data
    std::vector<float> vtxData = { 0.5f, -0.5f, 0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f, 0.5f,
                                   0.5f, -0.5f, -0.5f, 0.5f, -0.5f, 0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, 0.5f,
                                   0.5f, 0.5f, -0.5f, 0.5f, 0.5f, 0.5f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f, 0.5f, -0.5f,
                                   -0.5f, 0.5f, -0.5f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f,
                                   0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f, -0.5f, -0.5f, -0.5f, -0.5f, 0.5f, -0.5f,
                                   -0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f, 0.5f, 0.5f, -0.5f, 0.5f };
    meshData.vtxData = static_cast<void*>(vtxData.data());
    meshData.vtxStride = sizeof(float) * VERTEX_DIMENSION_CNT;
    meshData.vtxOffset = 0;
    meshData.vtxCount = static_cast<unsigned int>(vtxData.size()) / VERTEX_DIMENSION_CNT;
    // prepare index data of mesh data
    std::vector<unsigned int> indData = {0, 2, 3, 0, 3, 1, 8, 4, 5, 8, 5, 9, 10, 6, 7, 10, 7, 11, 12, 13,
                                         14, 12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22, 20, 22, 23 };
    meshData.indData = static_cast<void*>(indData.data());
    meshData.type = UINT_TYPE;
    meshData.indCount = static_cast<unsigned int>(indData.size());
    // prepare bounding box data of mesh data, format:[minX, minY, minZ, maxX, maxY, maxZ]
    std::vector<float> boundingBox = {-0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f };
    meshData.boundingBox = static_cast<void*>(boundingBox.data());

    // create object_0
    bool occluderUpdateTranFlag = true;
    // 变换矩阵（transform matrix） 是一个4x4的矩阵，由物体的位置（position）向量、旋转（rotaion）向量和缩放（scale）向量计算得出，计算方法可参考网上
    // 教程https://learnopengl-cn.github.io/01%20Getting%20started/07%20Transformations/#_18。变换矩阵通常由渲染引擎提供。
    std::vector<float> occluderTransformMatrix = { 17.87464f, 0.0f, 0.0f, 0.0f,
                                                   0.0f, 9.9626f, 0.0f, 0.0f,
                                                   0.0f, 0.0f, 1.565418f, 0.0f,
                                                   -13.7125f, -0.8224754f, 7.0f, 1.0f };
    object_0.id = 0;
    object_0.meshId = 0;
    object_0.meshData = meshData;

    object_0.updateTranFlag = occluderUpdateTranFlag;
    object_0.transformMatrix = occluderTransformMatrix;
    object_0.position = Vec3( -13.7125f, -0.8224754f, 7.0f );
    object_0.rotation = Vec3( 0.0f, 0.0f, 0.0f );
    object_0.scale = Vec3( 14.74197f, 6.056467f, 1.565418f );
    senceObjArray.push_back(object_0);

    // cretae object_1:
    Vec3 minBox_oc0(-0.5f, -0.5f, -0.5f);
    Vec3 maxBox_oc0(0.5f, 0.5f, 0.5f);
    bool TranFlag_oc0 = true;
    std::vector<float> TransformMatrix_oc0 = { 9.189964f, 0.0f, 0.0f, 0.0f,
                                               0.0f, 20.0f, 0.0f, 0.0f,
                                               0.0f, 0.0f, -2.92672f, 0.0f,
                                               -25.8f, -0.2f, 20.0f, 1.0f };
    object_1.id = 1;
    object_1.meshId = 1;
    object_1.meshData = meshData;
    object_1.minBox = minBox_oc0;
    object_1.maxBox = maxBox_oc0;
    object_1.updateTranFlag = TranFlag_oc0;
    object_1.transformMatrix = TransformMatrix_oc0;
    object_1.position = Vec3( -25.8f, -0.2f, 20.0f );
    object_1.rotation = Vec3( 0.0f, 0.0f, 0.0f );
    object_1.scale = Vec3( 9.189964f, 20.0f, -2.92672f );
    senceObjArray.push_back(object_1);

    // create object_2:
    Vec3 minBox_oc1(-0.5f, -0.5f, -0.5f);
    Vec3 maxBox_oc1(0.5f, 0.5f, 0.5f);
    bool TranFlag_oc1 = true;
    std::vector<float> TransformMatrix_oc1 = { 2.675584f, 0.0f, 0.0f, 0.0f,
                                               0.0f, 2.803216f, 0.0f, 0.0f,
                                               0.0f, 0.0f, 2.289755f, 0.0f,
                                               -3.4f, -3.4f, 2.89f, 1.0f };
    object_2.id = 2;
    object_2.meshId = 2;
    object_2.meshData = meshData;
    object_2.minBox = minBox_oc1;
    object_2.maxBox = maxBox_oc1;
    object_2.updateTranFlag = TranFlag_oc1;
    object_2.transformMatrix = TransformMatrix_oc1;
    object_2.position = Vec3( -3.4f, -3.4f, 2.89f );
    object_2.rotation = Vec3( 0.0f, 0.0f, 0.0f );
    object_2.scale = Vec3( 2.675584f, 2.803216f, 2.289755f );
    senceObjArray.push_back(object_2);

    // create object_3:
    Vec3 minBox_oc2(-0.5f, -0.5f, -0.5f);
    Vec3 maxBox_oc2(0.5f, 0.5f, 0.5f);
    bool TranFlag_oc2 = true;
    std::vector<float> TransformMatrix_oc2 = { 8.116322f, 0.0f, 0.0f, 0.0f,
                                               0.0f, 8.083576f, 0.0f, 0.0f,
                                               0.0f, 0.0f, 5.39309f, 0.0f,
                                               -12.0f, -1.02f, 12.95f, 1.0f };
    object_3.id = 3;
    object_3.meshId = 3;
    object_3.meshData = meshData;
    object_3.minBox = minBox_oc2;
    object_3.maxBox = maxBox_oc2;
    object_3.updateTranFlag = TranFlag_oc2;
    object_3.transformMatrix = TransformMatrix_oc2;
    object_3.position = Vec3( -12.0f, -1.02f, 12.95f );
    object_3.rotation = Vec3( 0.0f, 0.0f, 0.0f );
    object_3.scale = Vec3( 8.116322f, 8.083576f, 5.39309f );
    senceObjArray.push_back(object_3);
}

void CullingDemo()
{
    // 首先搭建场景，本场景包含4个物体
    CreateSence(senceObjArray);
    // 然后再创建culling实例，进行遮挡计算
    int goodcullingId = 0;
    // prepare view matrix
    std::vector<float> viewMatrix = { 1.0f, 0.0f, 0.0f, 0.0f,
                                      0.0f, 1.0f, 0.0f, 0.0f,
                                      0.0f, 0.0f, -1.0f, 0.0f,
                                      10.0f, -1.0f, -10.0f, 1.0f };
    // prepare projection matrix
    std::vector<float> projMatrix = { 0.9719149f, 0.0f, 0.0f, 0.0f,
                                      0.0f, 1.732051f, 0.0f, 0.0f,
                                      0.0f, 0.0f, -1.0006f, -1.0f,
                                      0.0f, 0.0f, -0.60018f, 0.0f };

    goodcullingId = CreateGoodCulling();
    UpdateViewMatrix(goodcullingId, &viewMatrix[0]);
    UpdateProjectionMatrix(goodcullingId, &projMatrix[0]);
    CleanUp(goodcullingId);

    AddOccluder(senceObjArray[0].meshId, senceObjArray[0].meshData);
    UpdateOccluderInfo(goodcullingId, senceObjArray[0].id, senceObjArray[0].meshId, senceObjArray[0].updateTranFlag,
                       &senceObjArray[0].transformMatrix[0]);
    AddOccludee(senceObjArray[1].meshId, GetBoundingBox(senceObjArray[1].minBox),
                GetBoundingBox(senceObjArray[1].maxBox));
    UpdateOccludeeInfo(goodcullingId, senceObjArray[1].id, senceObjArray[1].meshId, senceObjArray[1].updateTranFlag,
                       &senceObjArray[1].transformMatrix[0]);
    AddOccludee(senceObjArray[2].meshId, GetBoundingBox(senceObjArray[2].minBox),
                GetBoundingBox(senceObjArray[2].maxBox));
    UpdateOccludeeInfo(goodcullingId, senceObjArray[2].id, senceObjArray[2].meshId, senceObjArray[2].updateTranFlag,
                       &senceObjArray[2].transformMatrix[0]);
    AddOccludee(senceObjArray[3].meshId, GetBoundingBox(senceObjArray[3].minBox),
                GetBoundingBox(senceObjArray[3].maxBox));
    UpdateOccludeeInfo(goodcullingId, senceObjArray[3].id, senceObjArray[3].meshId, senceObjArray[3].updateTranFlag,
                       &senceObjArray[3].transformMatrix[0]);

    // rasterization and culling
    RasterizationAndCulling(goodcullingId);
    bool result = GetCullingResult(goodcullingId, senceObjArray[1].id);
    LOGI("occludee object_1 is visible: %d \n", result);       // 1, visible
    result = GetCullingResult(goodcullingId, senceObjArray[2].id);
    LOGI("occludee object_2 is visible: %d \n", result);     // 1, visible
    result = GetCullingResult(goodcullingId, senceObjArray[3].id);
    LOGI("occludee object_3 is visible: %d \n", result);      // 0, unvisible

    // clear resource
    Disable(goodcullingId);
    RemoveAllOccluders();
    RemoveAllOccludees();
    DestroyGoodCulling(goodcullingId);
}
extern "C"
JNIEXPORT void JNICALL Java_com_huawei_hms_scene_demo_goodculling_MainActivity_runDemo(JNIEnv *env, jclass) {
    CullingDemo();
}