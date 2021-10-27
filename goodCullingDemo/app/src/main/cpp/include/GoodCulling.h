/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2021. All rights reserved.
 * Description: OCCore
 * Author: Fields Lab
 * Create: 2020-12-01
 */

#ifndef GOOD_CULLING_H
#define GOOD_CULLING_H

#ifdef __ANDROID__
#define GOODCULLING_API __attribute__((visibility("default")))
#else
#define GOODCULLING_API __declspec(dllexport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Size of Matrix4*4, for projection matrix and view matrix
 */
constexpr int MAT4X4_SIZE = 16;

/*
 * The return code of culling API
 */
enum RtnCode {
    RTN_OK = 0,
    RTN_ERR,
    RTN_CULLING_ID_INVALID,
    RTN_CULLING_NOT_ENABLE,
    RTN_PARA_INVALID,
    RTN_CODE_NUM
};

/*
 * The type of index buffer
 */
enum IndexBufferType {
    UINT_TYPE = 0,
    USHORT_TYPE = 1,
    UBYTE_TYPE = 2,
    TYPE_NUM
};

/*
 * The winding order of the backface
 */
enum BackFaceWinding {
    /* Clockwise */
    GC_CW = 0,
    /* Counter-clockwise */
    GC_CCW,
    /* No backface culling */
    GC_NONE,
};

/*
 * The struct of occluder mesh data
 */
struct OccluderData {
    void* vtxData = nullptr;
    unsigned int vtxStride = 0;
    unsigned int vtxOffset = 0;
    unsigned int vtxCount = 0;
    void* indData = nullptr;
    IndexBufferType type = UINT_TYPE;
    unsigned int indCount = 0;
    void* boundingBox = nullptr; /* minX, minY, minZ, maxX, maxY, maxZ */
    BackFaceWinding winding = GC_CW;
};

/*
 * The struct of GoodCulling configuration
 */
struct ConfigData {
    bool bUpdateColor = false;
    bool bUseNeon = false;
    bool bUseMultiThread = false;
    bool bUseLastMVP = false;
    bool bUseOptCCW = false;
    bool bUseVeticesFirst = false;
    bool bUseSkipFrame = false;
    bool bFrustumCulling = false;
};

/*
 * @brief Create a culling instance, which will be used by other APIs
 *
 * @return Will return -1 if failed, returns a number between 0 and 9 representing the id of culling instance otherwise
 */
GOODCULLING_API int CreateGoodCulling();

/*
 * @brief Destroy a culling instance.
 *
 * @param id of the culling instance
 */
GOODCULLING_API void DestroyGoodCulling(int cullingId);

/*
 * @brief Remove all occludee mesh data from the global data which will be visited by all instances.
 */
GOODCULLING_API void RemoveAllOccludees();

/*
 * @brief Remove all occluder mesh data from the global data which will be visited by all instances
 */
GOODCULLING_API void RemoveAllOccluders();

/*
 * @brief Remove an occludee mesh data from the global data which will be visited by all instances
 *
 * @param id of the occludee mesh data
 * @return Will return a RtnCode value representing the result
 */
GOODCULLING_API RtnCode RemoveOccludee(int occludeeMeshId);

/*
 * @brief Remove an occluder mesh data from the global data which will be visited by all instances.
 *
 * @param id of the occluder mesh data
 * @return Will return a RtnCode value representing the result
 */
GOODCULLING_API RtnCode RemoveOccluder(int occluderMeshId);

/*
 * @brief Add an occluder mesh data to the global data which will be visited by all instances
 *
 * @param id of the occluder mesh data
 * @param the struct of occluder mesh data
 * @return Will return a RtnCode value representing the result
 */
GOODCULLING_API RtnCode AddOccluder(int occluderMeshId, OccluderData occluderData);

/*
 * @brief Add an occludee mesh data (which is a axis-aligned bounding box) to the global data which
 * will be visited by all instances
 *
 * @param id of the occludee mesh data
 * @param minBox pointer to float array(minX, minY, minZ)
 * @param maxBox pointer to float array(maxX, maxY, maxZ)
 * @return Will return a RtnCode value representing the result
 */
GOODCULLING_API RtnCode AddOccludee(int occludeeMeshId, const float* minBox, const float* maxBox);

/*
 * @brief Enable the culling instance.
 *
 * @param id of the culling instance
 */
GOODCULLING_API void Enable(int cullingId);

/*
 * @brief Disable the culling instance.
 *
 * @param id of the culling instance
 */
GOODCULLING_API void Disable(int cullingId);

/*
 * @brief Get the state of the culling instance.
 *
 * @param id of the culling instance
 * @return Will return true if enabled, false otherwise.
 */
GOODCULLING_API bool IsEnabled(int cullingId);

/*
 * @brief Clean up the result of rasterization, culling result and occluders and occludees' info to be rasterized
 *
 * @param id of the culling instance
 * @return Will return a RtnCode value representing the result
 */
GOODCULLING_API RtnCode CleanUp(int cullingId);

/*
 * @brief Update the view matrix of the camera
 *
 * @param id of the culling instance
 * @param Pointer to float array with length 16 (stored in column-major order) representing a view matrix
 * @return Will return a RtnCode value representing the result
 */
GOODCULLING_API RtnCode UpdateViewMatrix(int cullingId, const float* viewMatrix);

/*
 * @brief Update the projection matrix of the camera
 *
 * @param id of the culling instance
 * @param Pointer to float array with length 16 (stored in column-major order) representing a projection matrix
 * @return Will return a RtnCode value representing the result
 */
GOODCULLING_API RtnCode UpdateProjectionMatrix(int cullingId, const float* projMatrix);

/*
 * @brief Updata the occluder object use which mesh to be rasterized and the transform matrix of the occluder
 *        add this occluder to the set which will be rasterized in the frame
 *        if Cleanup is called, the set which will be rasterized will be clean up
 *
 * @param id of the culling instance
 * @param id of the occluder
 * @param id of the occluder mesh data
 * @param flag of the update transformMatrix
 * @param Pointer to float array with length 16 (stored in column-major order) representing a transform matrix
 * @return Will return a RtnCode value representing the result
 */
GOODCULLING_API RtnCode UpdateOccluderInfo(int cullingId, int occluderId, int occluderMeshId, bool updateTranFlag,
    const float* transformMatrix);

/*
 * @brief Updata the occludee object use which mesh to be rasterized and the transform matrix of the occludee
 *        add this occludee to the set which will be rasterized in the frame
 *        if Cleanup is called, the set which will be rasterized will be clean up
 *
 * @param id of the culling instance
 * @param id of the occludee
 * @param id of the occludee mesh data
 * @param flag of the update transformMatrix
 * @param Pointer to float array with length 16 (stored in column-major order) representing a transform matrix
 * @return Will return a RtnCode value representing the result
 */
GOODCULLING_API RtnCode UpdateOccludeeInfo(int cullingId, int occludeeId, int occludeeMeshId, bool updateTranFlag,
    const float* transformMatrix);

/*
 * @brief Rasterize the meshes and updating the culling result
 *
 * @param id of the culling instance
 * @return Will return a RtnCode value representing the result
 */
GOODCULLING_API RtnCode RasterizationAndCulling(int cullingId);

/*
 * @brief Get the visibility of the occludee after the call of RasterizationAndCulling interface
 *
 * @param id of the culling instance
 * @param id of the occludee
 * @return Will return a bool value representing the result, true: visible; false: invisible
 */
GOODCULLING_API bool GetCullingResult(int cullingId, int occludeeId);

/*
 * @brief Set the configuration of the culling instance
 *
 *
 * @param id of the culling instance
 * @param Pointer to struct of configuration data
 * @return Will return a RtnCode value representing the result
 */
GOODCULLING_API RtnCode SetConfig(int cullingId, const ConfigData* evtData);

#ifdef __cplusplus
};
#endif

#endif // GOOD_CULLING_H
