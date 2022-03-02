#ifndef RAYLIB_CPP_HPP
#define RAYLIB_CPP_HPP

#ifdef RAYEXT_IMPLEMENTATION
#define RAYGUI_IMPLEMENTATION
#endif

#include <string>
#include <raylib.h>
#include <raygui.h>
#include <rlgl.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <raymath.h>

#ifdef __cplusplus
}
#endif

/* Vector2 */

bool operator==(const Vector2 &v1, const Vector2 &v2) noexcept;
Vector2 operator+(const Vector2 &v1, const Vector2 &v2) noexcept;
Vector2 operator-(const Vector2 &v1, const Vector2 &v2) noexcept;
Vector2 operator-(const Vector2 &v) noexcept;
Vector2 operator*(const Vector2 &v, const float &f) noexcept;
Vector2 operator/(const Vector2 &v, const float &f);
Vector2& operator+=(Vector2 &v1, const Vector2 &v2) noexcept;
Vector2& operator-=(Vector2 &v1, const Vector2 &v2) noexcept;
Vector2& operator*=(Vector2 &v, const float &f) noexcept;
Vector2& operator/=(Vector2 &v, const float &f);

/* Vector3 */

bool operator==(const Vector3 &v1, const Vector3 &v2) noexcept;
Vector3 operator+(const Vector3 &v1, const Vector3 &v2) noexcept;
Vector3 operator-(const Vector3 &v1, const Vector3 &v2) noexcept;
Vector3 operator-(const Vector3 &v) noexcept;
Vector3 operator*(const Vector3 &v, const float &f) noexcept;
Vector3 operator/(const Vector3 &v, const float &f);
Vector3& operator+=(Vector3 &v1, const Vector3 &v2) noexcept;
Vector3& operator-=(Vector3 &v1, const Vector3 &v2) noexcept;
Vector3& operator*=(Vector3 &v, const float &f) noexcept;
Vector3& operator/=(Vector3 &v, const float &f);

/* Vector4/Quaternion */

bool operator==(const Vector4 &v1, const Vector4 &v2) noexcept;
Vector4 operator+(const Vector4 &v1, const Vector4 &v2) noexcept;
Vector4 operator-(const Vector4 &v1, const Vector4 &v2) noexcept;
Vector4 operator-(const Vector4 &v) noexcept;
Vector4 operator*(const Vector4 &v, const float &f) noexcept;
Vector4 operator/(const Vector4 &v, const float &f);
Vector4& operator+=(Vector4 &v1, const Vector4 &v2) noexcept;
Vector4& operator-=(Vector4 &v1, const Vector4 &v2) noexcept;
Vector4& operator*=(Vector4 &v, const float &f) noexcept;
Vector4& operator/=(Vector4 &v, const float &f);

/* Matrix */

Matrix operator+(const Matrix &m1, const Matrix &m2) noexcept;
Matrix operator-(const Matrix &m1, const Matrix &m2) noexcept;
Matrix operator*(const Matrix &m1, const Matrix &m2) noexcept;
Matrix& operator+=(Matrix &m1, const Matrix &m2) noexcept;
Matrix& operator-=(Matrix &m1, const Matrix &m2) noexcept;
Matrix& operator*=(Matrix &m1, const Matrix &m2) noexcept;

/* Core */

inline void 
InitWindow(int width, int height, const std::string &title);

inline void 
SetWindowTitle(const std::string &title);

inline void
SetClipboardText(const std::string &text);

inline Shader
LoadShader(const std::string &vsFileName, const std::string &fsFileName);

inline Shader
LoadShaderFromMemory(const std::string &vsCode, const std::string &fsCode);

inline int
GetShaderLocation(Shader shader, const std::string &uniformName);

inline int
GetShaderLocationAttrib(Shader shader, const std::string &attribName);

inline void 
TakeScreenshot(const std::string &fileName);

inline unsigned char *
LoadFileData(const std::string &fileName, unsigned int *bytesRead);

inline bool
SaveFileData(const std::string &fileName, void *data, unsigned int bytesToWrite);

inline char *
LoadFileText(const std::string &fileName);

inline bool
SaveFileText(const std::string &fileName, char *text);

inline bool
FileExists(const std::string &fileName);

inline bool
DirectoryExists(const std::string &dirPath);

inline bool
IsFileExtension(const std::string &fileName, const std::string &ext);

inline const char *
GetFileExtension(const std::string &fileName);

inline const char *
GetFileName(const std::string &filePath);

inline const char *
GetFileNameWithoutExt(const std::string &filePath);

inline const char *
GetDirectoryPath(const std::string &filePath);

inline const char *
GetPrevDirectoryPath(const std::string &dirPath);

inline bool
ChangeDirectory(const std::string &dir);

inline long
GetFileModTime(const std::string &fileName);

inline void
OpenURL(const std::string &url);

/* Textures */

inline Image
LoadImage(const std::string &fileName);

inline Image
LoadImageRaw(const std::string &fileName, int width, int height, int format, 
             int headerSize);

inline Image
LoadImageAnim(const std::string &fileName, int *frames);

inline Image
LoadImageFromMemory(const std::string &fileType, const unsigned char *fileData,
                    int dataSize);

inline bool
ExportImage(Image image, const std::string &fileName);

inline bool
ExportImageAsCode(Image image, const std::string &fileName);

inline Image
ImageText(const std::string &text, int fontSize, Color color);

inline Image
ImageTextEx(Font font, const std::string &text, float fontSize, float spacing,
            Color tint);

inline void
ImageDrawText(Image *dst, const std::string &text, int posX, int posY,
              int fontSize, Color color);

inline void
ImageDrawTextEx(Image *dst, Font font, const std::string &text,
                Vector2 position, float fontSize, float spacing, Color tint);

inline Texture2D
LoadTexture(const std::string &fileName);

/* Text */

inline Font
LoadFont(const std::string &fileName);

inline Font
LoadFontEx(const std::string &fileName, int fontSize, int *fontChars,
           int glyphCount);

inline Font
LoadFontFromMemory(const std::string &fileType, const unsigned char *fileData,
                   int dataSize, int fontSize, int *fontChars, int glyphCount);

inline void
DrawText(const std::string &text, int posX, int posY, int fontSize, Color color);

inline void
DrawTextEx(Font font, const std::string &text, Vector2 position, float fontSize,
           float spacing, Color tint);

inline void
DrawTextPro(Font font, const std::string &text, Vector2 position,
            Vector2 origin, float rotation, float fontSize, float spacing,
            Color tint);

inline int
MeasureText(const std::string &text, int fontSize);

inline Vector2
MeasureTextEx(Font font, const std::string &text, float fontSize, float spacing);

inline int*
LoadCodepoints(const std::string &text, int *count);

inline int
GetCodepointCount(const std::string &text);

inline int
GetCodepoint(const std::string &text, int *bytesProcessed);

/* Models */

inline Model
LoadModel(const std::string &fileName);

inline bool
ExportMesh(Mesh mesh, const std::string &fileName);

inline Material*
LoadMaterials(const std::string &fileName, int *materialCount);

inline ModelAnimation*
LoadModelAnimations(const std::string &fileName, unsigned int *animCount);

/* Audio */

inline Wave
LoadWave(const std::string &fileName);

inline Wave
LoadWaveFromMemory(const std::string &fileType, const unsigned char *fileData,
                   int dataSize);

inline Sound
LoadSound(const std::string &fileName);

inline bool
ExportWave(Wave wave, const std::string &fileName);

inline bool
ExportWaveAsCode(Wave wave, const std::string &fileName);

inline Music
LoadMusicStream(const std::string &fileName);

inline Music
LoadMusicStreamFromMemory(const std::string &fileType, unsigned char *data,
                          int dataSize);


#ifdef RAYEXT_IMPLEMENTATION

/* Vector2 */

bool
operator==(const Vector2 &v1, const Vector2 &v2)
noexcept
{
    return v1.x == v2.x && v1.y == v2.y;
}

Vector2 
operator+(const Vector2 &v1, const Vector2 &v2)
noexcept
{
    return Vector2Add(v1, v2);
}

Vector2 
operator-(const Vector2 &v1, const Vector2 &v2)
noexcept
{
    return Vector2Subtract(v1, v2);
}

Vector2
operator-(const Vector2 &v)
noexcept
{
    return Vector2Negate(v);
}

Vector2 
operator*(const Vector2 &v, const float &f)
noexcept
{
    return Vector2Scale(v, f);
}

Vector2 
operator/(const Vector2 &v, const float &f)
{
    return Vector2Scale(v, 1 / f);
}

Vector2&
operator+=(Vector2 &v1, const Vector2 &v2)
noexcept
{
    v1.x += v2.x;
    v1.y += v2.y;
    return v1;
}

Vector2&
operator-=(Vector2 &v1, const Vector2 &v2)
noexcept
{
    v1.x -= v2.x;
    v1.y -= v2.y;
    return v1;
}

Vector2&
operator*=(Vector2 &v, const float &f)
noexcept
{
    v.x *= f;
    v.y *= f;
    return v;
}

Vector2&
operator/=(Vector2 &v, const float &f)
{
    v.x /= f;
    v.y /= f;
    return v;
}

/* Vector3 */

bool
operator==(const Vector3 &v1, const Vector3 &v2)
noexcept
{
    return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
}

Vector3 
operator+(const Vector3 &v1, const Vector3 &v2)
noexcept
{
    return Vector3Add(v1, v2);
}

Vector3 
operator-(const Vector3 &v1, const Vector3 &v2)
noexcept
{
    return Vector3Subtract(v1, v2);
}

Vector3
operator-(const Vector3 &v)
noexcept
{
    return Vector3Negate(v);
}

Vector3 
operator*(const Vector3 &v, const float &f)
noexcept
{
    return Vector3Scale(v, f);
}

Vector3 
operator/(const Vector3 &v, const float &f)
{
    return Vector3Scale(v, 1 / f);
}

Vector3&
operator+=(Vector3 &v1, const Vector3 &v2)
noexcept
{
    v1.x += v2.x;
    v1.y += v2.y;
    v1.z += v2.z;
    return v1;
}

Vector3&
operator-=(Vector3 &v1, const Vector3 &v2)
noexcept
{
    v1.x -= v2.x;
    v1.y -= v2.y;
    v1.z -= v2.z;
    return v1;
}

Vector3&
operator*=(Vector3 &v, const float &f)
noexcept
{
    v.x *= f;
    v.y *= f;
    v.z *= f;
    return v;
}

Vector3&
operator/=(Vector3 &v, const float &f)
{
    v.x /= f;
    v.y /= f;
    v.z /= f;
    return v;
}

/* Vector4/Quaternion */

bool
operator==(const Vector4 &v1, const Vector4 &v2)
noexcept
{
    return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
}

Vector4 
operator+(const Vector4 &v1, const Vector4 &v2)
noexcept
{
    return QuaternionAdd(v1, v2);
}

Vector4 
operator-(const Vector4 &v1, const Vector4 &v2)
noexcept
{
    return QuaternionSubtract(v1, v2);
}

Vector4
operator-(const Vector4 &v)
noexcept
{
    return QuaternionScale(v, -1);
}

Vector4 
operator*(const Vector4 &v, const float &f)
noexcept
{
    return QuaternionScale(v, f);
}

Vector4 
operator/(const Vector4 &v, const float &f)
{
    return QuaternionScale(v, 1 / f);
}

Vector4&
operator+=(Vector4 &v1, const Vector4 &v2)
noexcept
{
    v1.x += v2.x;
    v1.y += v2.y;
    v1.z += v2.z;
    v1.w += v2.w;
    return v1;
}

Vector4&
operator-=(Vector4 &v1, const Vector4 &v2)
noexcept
{
    v1.x -= v2.x;
    v1.y -= v2.y;
    v1.z -= v2.z;
    v1.w -= v2.w;
    return v1;
}

Vector4&
operator*=(Vector4 &v, const float &f)
noexcept
{
    v.x *= f;
    v.y *= f;
    v.z *= f;
    v.w *= f;
    return v;
}

Vector4&
operator/=(Vector4 &v, const float &f)
{
    v.x /= f;
    v.y /= f;
    v.z /= f;
    v.w /= f;
    return v;
}

/* Matrix */

Matrix 
operator+(const Matrix &m1, const Matrix &m2)
noexcept
{
    return MatrixAdd(m1, m2);
}

Matrix 
operator-(const Matrix &m1, const Matrix &m2)
noexcept
{
    return MatrixSubtract(m1, m2);
}

Matrix 
operator*(const Matrix &m1, const Matrix &m2)
noexcept
{
    return MatrixMultiply(m1, m2);
}

Matrix&
operator+=(Matrix &m1, const Matrix &m2)
noexcept
{
    m1 = MatrixAdd(m1, m2);
    return m1;
}

Matrix&
operator-=(Matrix &m1, const Matrix &m2)
noexcept
{
    m1 = MatrixSubtract(m1, m2);
    return m1;
}

Matrix&
operator*=(Matrix &m1, const Matrix &m2)
noexcept
{
    m1 = MatrixMultiply(m1, m2);
    return m1;
}

/* Core */

inline void 
InitWindow(int width, int height, const std::string &title)
{
    InitWindow(width, height, title.c_str());
}

inline void 
SetWindowTitle(const std::string &title)
{
    SetWindowTitle(title.c_str());
}

inline void
SetClipboardText(const std::string &text)
{
    SetClipboardText(text.c_str());
}

inline Shader
LoadShader(const std::string &vsFileName, const std::string &fsFileName)
{
    return LoadShader(vsFileName.c_str(), fsFileName.c_str());
}

inline Shader
LoadShaderFromMemory(const std::string &vsCode, const std::string &fsCode)
{
    return LoadShaderFromMemory(vsCode.c_str(), fsCode.c_str());
}

inline int
GetShaderLocation(Shader shader, const std::string &uniformName)
{
    return GetShaderLocation(shader, uniformName.c_str());
}

inline int
GetShaderLocationAttrib(Shader shader, const std::string &attribName)
{
    return GetShaderLocationAttrib(shader, attribName.c_str());
}

inline void 
TakeScreenshot(const std::string &fileName)
{
    TakeScreenshot(fileName.c_str());
}

inline unsigned char *
LoadFileData(const std::string &fileName, unsigned int *bytesRead)
{
    return LoadFileData(fileName.c_str(), bytesRead);
}

inline bool
SaveFileData(const std::string &fileName, void *data, unsigned int bytesToWrite)
{
    return SaveFileData(fileName.c_str(), data, bytesToWrite);
}

inline char *
LoadFileText(const std::string &fileName)
{
    return LoadFileText(fileName.c_str());
}

inline bool
SaveFileText(const std::string &fileName, char *text)
{
    return SaveFileText(fileName.c_str(), text);
}

inline bool
FileExists(const std::string &fileName)
{
    return FileExists(fileName.c_str());
}

inline bool
DirectoryExists(const std::string &dirPath)
{
    return DirectoryExists(dirPath.c_str());
}

inline bool
IsFileExtension(const std::string &fileName, const std::string &ext)
{
    return IsFileExtension(fileName.c_str(), ext.c_str());
}

inline const char *
GetFileExtension(const std::string &fileName)
{
    return GetFileExtension(fileName.c_str());
}

inline const char *
GetFileName(const std::string &filePath)
{
    return GetFileName(filePath.c_str());
}

inline const char *
GetFileNameWithoutExt(const std::string &filePath)
{
    return GetFileNameWithoutExt(filePath.c_str());
}

inline const char *
GetDirectoryPath(const std::string &filePath)
{
    return GetDirectoryPath(filePath.c_str());
}

inline const char *
GetPrevDirectoryPath(const std::string &dirPath)
{
    return GetPrevDirectoryPath(dirPath.c_str());
}

inline bool
ChangeDirectory(const std::string &dir)
{
    return ChangeDirectory(dir.c_str());
}

inline long
GetFileModTime(const std::string &fileName)
{
    return GetFileModTime(fileName.c_str());
}

inline void
OpenURL(const std::string &url)
{
    return OpenURL(url.c_str());
}

/* Textures */

inline Image
LoadImage(const std::string &fileName)
{
    return LoadImage(fileName.c_str());
}

inline Image
LoadImageRaw(const std::string &fileName, int width, int height, int format, 
             int headerSize)
{
    return LoadImageRaw(fileName.c_str(), width, height, format, headerSize);
}

inline Image
LoadImageAnim(const std::string &fileName, int *frames)
{
    return LoadImageAnim(fileName.c_str(), frames);
}

inline Image
LoadImageFromMemory(const std::string &fileType, const unsigned char *fileData,
                    int dataSize)
{
    return LoadImageFromMemory(fileType.c_str(), fileData, dataSize);
}

inline bool
ExportImage(Image image, const std::string &fileName)
{
    return ExportImage(image, fileName.c_str());
}

inline bool
ExportImageAsCode(Image image, const std::string &fileName)
{
    return ExportImageAsCode(image, fileName.c_str());
}

inline Image
ImageText(const std::string &text, int fontSize, Color color)
{
    return ImageText(text.c_str(), fontSize, color);
}

inline Image
ImageTextEx(Font font, const std::string &text, float fontSize, float spacing,
            Color tint)
{
    return ImageTextEx(font, text.c_str(), fontSize, spacing, tint);
}

inline void
ImageDrawText(Image *dst, const std::string &text, int posX, int posY,
              int fontSize, Color color)
{
    ImageDrawText(dst, text.c_str(), posX, posY, fontSize, color);
}

inline void
ImageDrawTextEx(Image *dst, Font font, const std::string &text,
                Vector2 position, float fontSize, float spacing, Color tint)
{
    ImageDrawTextEx(dst, font, text.c_str(), position, fontSize, spacing, tint);
}

inline Texture2D
LoadTexture(const std::string &fileName)
{
    return LoadTexture(fileName.c_str());
}

/* Text */

inline Font
LoadFont(const std::string &fileName)
{
    return LoadFont(fileName.c_str());
}

inline Font
LoadFontEx(const std::string &fileName, int fontSize, int *fontChars,
           int glyphCount)
{
    return LoadFontEx(fileName.c_str(), fontSize, fontChars, glyphCount);
}

inline Font
LoadFontFromMemory(const std::string &fileType, const unsigned char *fileData,
                   int dataSize, int fontSize, int *fontChars, int glyphCount)
{
    return LoadFontFromMemory(fileType.c_str(), fileData, dataSize, fontSize,
                              fontChars, glyphCount);
}

inline void
DrawText(const std::string &text, int posX, int posY, int fontSize, Color color)
{
    DrawText(text.c_str(), posX, posY, fontSize, color);
}

inline void
DrawTextEx(Font font, const std::string &text, Vector2 position, float fontSize,
           float spacing, Color tint)
{
    DrawTextEx(font, text.c_str(), position, fontSize, spacing, tint);
}

inline void
DrawTextPro(Font font, const std::string &text, Vector2 position,
            Vector2 origin, float rotation, float fontSize, float spacing,
            Color tint)
{
    DrawTextPro(font, text.c_str(), position, origin, rotation, fontSize,
                spacing, tint);
}

inline int
MeasureText(const std::string &text, int fontSize)
{
    return MeasureText(text.c_str(), fontSize);
}

inline Vector2
MeasureTextEx(Font font, const std::string &text, float fontSize, float spacing)
{
    return MeasureTextEx(font, text.c_str(), fontSize, spacing);
}

inline int*
LoadCodepoints(const std::string &text, int *count)
{
    return LoadCodepoints(text.c_str(), count);
}

inline int
GetCodepointCount(const std::string &text)
{
    return GetCodepointCount(text.c_str());
}

inline int
GetCodepoint(const std::string &text, int *bytesProcessed)
{
    return GetCodepoint(text.c_str(), bytesProcessed);
}

/* Models */

inline Model
LoadModel(const std::string &fileName)
{
    return LoadModel(fileName.c_str());
}

inline bool
ExportMesh(Mesh mesh, const std::string &fileName)
{
    return ExportMesh(mesh, fileName.c_str());
}

inline Material*
LoadMaterials(const std::string &fileName, int *materialCount)
{
    return LoadMaterials(fileName.c_str(), materialCount);
}

inline ModelAnimation*
LoadModelAnimations(const std::string &fileName, unsigned int *animCount)
{
    return LoadModelAnimations(fileName.c_str(), animCount);
}

/* Audio */

inline Wave
LoadWave(const std::string &fileName)
{
    return LoadWave(fileName.c_str());
}

inline Wave
LoadWaveFromMemory(const std::string &fileType, const unsigned char *fileData,
                   int dataSize)
{
    return LoadWaveFromMemory(fileType.c_str(), fileData, dataSize);
}

inline Sound
LoadSound(const std::string &fileName)
{
    return LoadSound(fileName.c_str());
}

inline bool
ExportWave(Wave wave, const std::string &fileName)
{
    return ExportWave(wave, fileName.c_str());
}

inline bool
ExportWaveAsCode(Wave wave, const std::string &fileName)
{
    return ExportWaveAsCode(wave, fileName.c_str());
}

inline Music
LoadMusicStream(const std::string &fileName)
{
    return LoadMusicStream(fileName.c_str());
}

inline Music
LoadMusicStreamFromMemory(const std::string &fileType, unsigned char *data,
                          int dataSize)
{
    return LoadMusicStreamFromMemory(fileType.c_str(), data, dataSize);
}

#endif // RAYEXT_IMPLEMENTATION

#endif // RAYLIB_CPP_HPP
