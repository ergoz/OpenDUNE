/** @file src/file.h %File access definitions. */

#ifndef FILE_H
#define FILE_H

enum {
	FILE_MODE_READ       = 0x01,
	FILE_MODE_WRITE      = 0x02,
	FILE_MODE_READ_WRITE = FILE_MODE_READ | FILE_MODE_WRITE,

	FILE_MAX = 20,
	FILE_INVALID = 0xFF
};

/**
 * Static information about files and their location.
 */
typedef struct FileInfo {
	const char *filename;                                   /*!< Name of the file. */
	uint32 fileSize;                                        /*!< The size of this file. */
	void *buffer;                                           /*!< In case the file is read in the memory, this is the location of the data. */
	uint32 filePosition;                                    /*!< Where in the file we currently are (doesn't have to start at zero when in PAK file). */
	struct {
		BIT_U8 inMemory:1;                                  /*!< File is loaded in alloc'd memory. */
		BIT_U8 inPAKFile:1;                                 /*!< File can be in other PAK file. */
	} flags;                                                /*!< General flags of the FileInfo. */
} FileInfo;

extern uint16 g_fileOperation;

extern bool File_Init(void);
extern void File_Uninit(void);
extern bool File_Exists(const char *filename);
extern uint8 File_Open(const char *filename, uint8 mode);
extern void File_Close(uint8 index);
extern uint32 File_Read(uint8 index, void *buffer, uint32 length);
extern uint16 File_Read_LE16(uint8 index);
extern uint32 File_Read_LE32(uint8 index);
extern uint32 File_Write(uint8 index, void *buffer, uint32 length);
extern bool File_Write_LE16(uint8 index, uint16 value);
extern uint32 File_Seek(uint8 index, uint32 position, uint8 mode);
extern uint32 File_GetSize(uint8 index);
extern void File_Delete(const char *filename);
extern void File_Create(const char *filename);
extern uint32 File_ReadBlockFile(const char *filename, void *buffer, uint32 length);
extern void *File_ReadWholeFile(const char *filename);
extern uint16 *File_ReadWholeFileLE16(const char *filename);
extern uint32 File_ReadFile(const char *filename, void *buf);
extern uint8 ChunkFile_Open(const char *filename);
extern void ChunkFile_Close(uint8 index);
extern uint32 ChunkFile_Seek(uint8 index, uint32 header);
extern uint32 ChunkFile_Read(uint8 index, uint32 header, void *buffer, uint32 buflen);

extern FILE *fopendatadir(const char *name, const char *mode);
extern bool fread_le_uint32(uint32 *value, FILE *stream);
extern bool fread_le_uint16(uint16 *value, FILE *stream);
extern bool fwrite_le_uint32(uint32 value, FILE *stream);
extern bool fwrite_le_uint16(uint16 value, FILE *stream);
#define fread_le_int32(p, f) fread_le_uint32((uint32 *)(p), (f))
#define fread_le_int16(p, f) fread_le_uint16((uint16 *)(p), (f))
#define fwrite_le_int32(v, f) fwrite_le_uint32((uint32)(v), (f))
#define fwrite_le_int16(v, f) fwrite_le_uint16((uint16)(v), (f))

#endif /* FILE_H */
