#ifndef H__SRGS___INCLUDED
#define H__SRGS___INCLUDED

#include <stdint.h>
#include <string.h>



typedef struct srgs_t srgs_t;


typedef enum {
    srgs__object_render_mode__color,
    srgs__object_render_mode__texture,
    srgs__object_render_mode__none,
    srgs__object_render_mode__depth_only
} srgs__object_render_mode;

typedef enum {
    srgs__object_depth_mode__less,
    srgs__object_depth_mode__lessequal,
    srgs__object_depth_mode__equal,
    srgs__object_depth_mode__greater,
    srgs__object_depth_mode__greaterequal,
    srgs__object_depth_mode__always,
} srgs__object_depth_mode;

typedef enum {
    srgs__object_vertex_channel__position,
    srgs__object_vertex_channel__uvs,
    srgs__object_vertex_channel__color,
} srgs__object_vertex_channel;


srgs_t * srgs_create(
    uint32_t startW, uint32_t startH,

    // can be NULL. In that case, malloc() is used.
    void * (*allocatorFunction)  (size_t),

    // can be NULL. In that case, free() is used.
    void   (*deallocatorFunction)(void *),

    // can be NULL. In that case, realloc() is used.
    void * (*reallocatorFunction)(void *, size_t)


);

// Always defined. Never changes
uint32_t srgs_get_framebuffer_texture(const srgs_t *);

// Always defined. Never changes
uint32_t srgs_get_depthbuffer_texture(const srgs_t *);




void srgs_destroy(srgs_t *);





// texture API

uint32_t srgs_texture_create(srgs_t *, uint32_t w, uint32_t h);

int srgs_texture_verify(srgs_t *, uint32_t);

void srgs_texture_destroy(srgs_t *, uint32_t);

void srgs_texture_blank(srgs_t *, uint32_t, char white);

void srgs_texture_update(
    srgs_t *, 
    uint32_t,

    const uint8_t * src, 
    uint32_t xDest, uint32_t yDest, 
    uint32_t xSrc,  uint32_t ySrc,
    uint32_t wSrc,  uint32_t hSrc
);

void srgs_texture_resize(srgs_t *, uint32_t, uint32_t, uint32_t);

const uint8_t * srgs_texture_get_data(const srgs_t *, uint32_t);

uint32_t srgs_texture_get_width(const srgs_t *, uint32_t);

uint32_t srgs_texture_get_height(const srgs_t *, uint32_t);




// matrix API

typedef struct {
	  float x0, y0, z0, w0,
			x1, y1, z1, w1,
			x2, y2, z2, w2,
			x3, y3, z3, w3;
} srgs_matrix_t;

uint32_t srgs_matrix_create(srgs_t *);

int srgs_matrix_verify(srgs_t *, uint32_t);

void srgs_matrix_destroy(srgs_t *, uint32_t);



void srgs_matrix_set(srgs_t *, uint32_t, srgs_matrix_t *);

const srgs_matrix_t * srgs_matrix_get(const srgs_t *, uint32_t);




// object API

uint32_t srgs_object_create(srgs_t *);

int srgs_object_verify(srgs_t *, uint32_t);

uint32_t srgs_object_clone(srgs_t *, uint32_t);

void srgs_object_destroy(srgs_t *, uint32_t);

void srgs_object_set_vertex_count(srgs_t *, uint32_t, uint32_t);

// assumes the incoming buffer matches in size tot he actual buffer
void srgs_object_define_vertices(
    srgs_t *, 
    uint32_t, 
    srgs__object_vertex_channel, 
    float *
);

void srgs_object_update_vertices(
    srgs_t *, 
    uint32_t, 
    srgs__object_vertex_channel, 
    uint32_t fromVertexIndex, 
    uint32_t toVertexIndex, 
    float * src
);

const float * srgs_object_get_vertices(
    const srgs_t *, 
    int32_t,    
    srgs__object_vertex_channel
);


void srgs_object_set_render_mode(srgs_t *, uint32_t, srgs__object_render_mode);

void srgs_object_set_depth_mode(srgs_t *, uint32_t, srgs__object_depth_mode);


void srgs_object_set_texture(srgs_t *, uint32_t, uint32_t);

void srgs_object_set_transform(srgs_t *, uint32_t, uint32_t);


// any unneeded attribute can be set NULL and is ignored.
void srgs_object_get_parameters(
    const srgs_t *,
    uint32_t,
    
    srgs__object_render_mode *,
    srgs__object_depth_mode *,
    uint32_t * matrixID,
    uint32_t * textureID,
    uint32_t * vertexCount
);









uint32_t srgs_renderlist_create(srgs_t *);

int srgs_renderlist_verify(srgs_t *, uint32_t);

void srgs_renderlist_destroy(srgs_t *, uint32_t);

void srgs_renderlist_set_transform(srgs_t *, uint32_t, uint32_t);

void srgs_renderlist_set_objects(
    srgs_t *, 
    uint32_t list, 
    uint32_t count, 
    uint32_t * objectIDs
);



void srgs_render(srgs_t *, uint32_t count, uint32_t * renderListIDs);
























#ifdef SRGS__LINEAR_ALGEBRA


/* Vector utilities */


typedef struct {
    float x; float y; float z;
} srgs_vector3_t;

typedef struct {
    float x; float y; float z; float w;
} srgs_vector4_t;

typedef struct {
    float x; float y;
} srgs_vector2_t;





// Allocates a 4x1 matrix set to the identity -> (0, 0, 0, 1)
srgs_vector4_t * srgs_utility_new_vec4();

// Convenience constructors for platforms that dont support input static definition.
srgs_vector3_t SRGSVEC3(float x, float y, float z);
srgs_vector4_t SRGSVEC4(float x, float y, float z, float w);

// Sets a given vector to the given values
void srgs_utility_vec_set(srgs_vector4_t * vec, float x, float y, float z, float w);


// Sets dest to a X b
void srgs_utility_vec_cross(srgs_vector3_t * dest, const srgs_vector3_t * a, const srgs_vector3_t * b);

// Returns a (dot) b
float srgs_utility_vec_dot(const srgs_vector3_t * a, const srgs_vector3_t * b);


// returns the angle between 2 vectors in degrees
float srgs_utility_vec_theta(const srgs_vector3_t * a, const srgs_vector3_t * b);

// performs the dot product:  a . b
float srgs_utility_vec_dot(const srgs_vector3_t * a, const srgs_vector3_t * b);

// Returns the distance between a and b as positional vectors
float srgs_utility_vec_distance(const srgs_vector3_t * a, const srgs_vector3_t * b);

// convenience function for normalize((p1 - p2) x (p3 - p2))
srgs_vector3_t srgs_utility_surface_normal(const srgs_vector3_t * p1, const srgs_vector3_t * p2, const srgs_vector3_t * p3);


// Performs a "intersection test". Returns whether the line formed by 
// linePoint and linePoint2 intersects the surface defined by pl
int srgs_utility_intersection_test(
    const srgs_vector3_t * linePoint,
    const srgs_vector3_t * linePoint2,
    
    const srgs_vector3_t * surfaceP1,
    const srgs_vector3_t * surfaceP2,
    const srgs_vector3_t * surfaceP3,
    
    srgs_vector3_t * intersectResult
);

// Same as intersection_test except:
// - A line segment is specified rather than a ray 
// - The plane is defined in position-normal form. 
int srgs_utility_intersection_test_plane(
    const srgs_vector3_t * linePoint,
    const srgs_vector3_t * linePoint2,
    
    const srgs_vector3_t * planePoint,
    const srgs_vector3_t * planeNormal,
    
    srgs_vector3_t * intersectResult
);

// Retruns the length of the vector
float srgs_utility_vec_magnitude(const srgs_vector3_t * a);

// Sets srcdest to a normalized version of itself.
void srgs_utility_vec_normalize(srgs_vector3_t * srcdest);
















/* Matrix utilities */






/* Standard operations */


// Sets a matrix dest to the values of matrix src
void srgs_utility_matrix_set(srgs_matrix_t * dest, srgs_matrix_t * src);

// Sets a matrix dest to be the matrix formed by all the elements given
void srgs_utility_matrix_set_float(srgs_matrix_t * dest,
	float x0, float y0, float z0, float w0,
	float x1, float y1, float z1, float w1,
	float x2, float y2, float z2, float w2,
	float x3, float y3, float z3, float w3
);

//Sets the matrix to the identity matrix
void srgs_utility_matrix_set_identity(srgs_matrix_t * dest);

// Sets result to  A * B
srgs_matrix_t srgs_utility_matrix_multiply_(srgs_matrix_t * a, srgs_matrix_t * b);

// Sets result as the result of A * B
void srgs_utility_matrix_multiply(srgs_matrix_t * result, const srgs_matrix_t * a, const srgs_matrix_t * b);

// Sets result to A * B
void srgs_utility_matrix_vector_multiply(srgs_vector4_t * result, const srgs_matrix_t * a, const srgs_vector4_t * b);


// Print the matrix
void srgs_utility_matrix_print(srgs_matrix_t * mat);

// Returns a read-only reference to an identity matrix;
srgs_matrix_t * srgs_utility_matrix_get_identity();

// Converts the matrix into its inverse (A transform matrix will always have an inverse.)
void srgs_utility_matrix_invert(srgs_matrix_t *);







/* Transform operations */

// Multiplies the matrix to express a rotational transform about the axis defined by a vector x, y, z.
void srgs_utility_matrix_rotate(srgs_matrix_t *, float theta, float xAxis, float yAxis, float zAxis);

// Multiplies the matrix to express a translation by x, y, and z
void srgs_utility_matrix_translate(srgs_matrix_t *, float x, float y, float z);

// Multiplies the matrix to express a scaling by x, y and z amounts
void srgs_utility_matrix_scale(srgs_matrix_t *, float x, float y, float z);

// Sets the matrix to express the inverse major order of its current form.
// The Matrix set of functions deal with matrices that are expressed in column-major format
void srgs_utility_matrix_reverse_majority(srgs_matrix_t *);

// Convenvience function for matrix * c assuming matrix is a transform matrix 
// and c is a positional vector. Internally, c is stepped up to a 4-component vector with 1.0 as its w 
// to properly calculation the output vector.
srgs_vector3_t srgs_utility_matrix_transform(const srgs_matrix_t * matrix, const srgs_vector3_t * c);

srgs_vector3_t srgs_utility_matrix_get_xyz_rotation(const srgs_matrix_t * matrix);




/* Projection operations */

// Multiplies the matrix by an orthographic projection matrix
void srgs_utility_matrix_projection_orthographic(srgs_matrix_t *,
	float left, float right,
	float bottom, float top,
	float near, float far
);


// Multiplies the matrix by a perspective matrix
void srgs_utility_matrix_projection_perspective(srgs_matrix_t *,
    float fieldOfViewThetaY,
    float aspectRatioXtoY,
    float zNear, //< MUST be positive
    float zFar   //< MUST be positive
);


void srgs_utility_matrix_look_at(srgs_matrix_t *,
    const srgs_vector3_t * eyePosition,
    const srgs_vector3_t * targetPosition,
    const srgs_vector3_t * upVector
);



#endif









#endif

