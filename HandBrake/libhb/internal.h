/* $Id: internal.h,v 1.41 2005/11/25 15:05:25 titer Exp $

   This file is part of the HandBrake source code.
   Homepage: <http://handbrake.m0k.org/>.
   It may be used under the terms of the GNU General Public License. */

/***********************************************************************
 * common.c
 **********************************************************************/
void hb_log( char * log, ... );
void hb_error( char * fmt, ...);

int  hb_list_bytes( hb_list_t * );
void hb_list_seebytes( hb_list_t * l, uint8_t * dst, int size );
void hb_list_getbytes( hb_list_t * l, uint8_t * dst, int size,
                       uint64_t * pts, uint64_t * pos );
void hb_list_empty( hb_list_t ** );

hb_title_t * hb_title_init( char * dvd, int index );
void         hb_title_close( hb_title_t ** );

/***********************************************************************
 * hb.c
 **********************************************************************/
int  hb_get_pid( hb_handle_t * );
void hb_set_state( hb_handle_t *, hb_state_t * );

/***********************************************************************
 * fifo.c
 **********************************************************************/
struct hb_buffer_s
{
    int           size;
    int           alloc;
    uint8_t *     data;
    int           cur;

    int64_t       sequence;

    int           id;
    int64_t       start;
    int64_t       stop;
    int           new_chap;

#define HB_FRAME_IDR    0x01
#define HB_FRAME_I      0x02
#define HB_FRAME_AUDIO  0x04
#define HB_FRAME_P      0x10
#define HB_FRAME_B      0x20
#define HB_FRAME_BREF   0x40
#define HB_FRAME_KEY    0x0F
#define HB_FRAME_REF    0xF0
    uint8_t       frametype;
    uint16_t       flags;

    /* Holds the output PTS from x264, for use by b-frame offsets in muxmp4.c */
    int64_t     renderOffset;

    int           x;
    int           y;
    int           width;
    int           height;

    hb_buffer_t * sub;

    hb_buffer_t * next;
};

void hb_buffer_pool_init( void );
void hb_buffer_pool_free( void );

hb_buffer_t * hb_buffer_init( int size );
void          hb_buffer_realloc( hb_buffer_t *, int size );
void          hb_buffer_close( hb_buffer_t ** );
void          hb_buffer_copy_settings( hb_buffer_t * dst, 
                                       const hb_buffer_t * src );

hb_fifo_t   * hb_fifo_init();
int           hb_fifo_size( hb_fifo_t * );
int           hb_fifo_is_full( hb_fifo_t * );
float         hb_fifo_percent_full( hb_fifo_t * f );
hb_buffer_t * hb_fifo_get( hb_fifo_t * );
hb_buffer_t * hb_fifo_see( hb_fifo_t * );
hb_buffer_t * hb_fifo_see2( hb_fifo_t * );
void          hb_fifo_push( hb_fifo_t *, hb_buffer_t * );
void          hb_fifo_close( hb_fifo_t ** );

/***********************************************************************
 * Threads: update.c, scan.c, work.c, reader.c, muxcommon.c
 **********************************************************************/
hb_thread_t * hb_update_init( int * build, char * version );
hb_thread_t * hb_scan_init( hb_handle_t *, const char * path,
                            int title_index, hb_list_t * list_title );
hb_thread_t * hb_work_init( hb_list_t * jobs, int cpu_count,
                            volatile int * die, int * error, hb_job_t ** job );
hb_thread_t  * hb_reader_init( hb_job_t * );
hb_thread_t  * hb_muxer_init( hb_job_t * );

/***********************************************************************
 * libmpeg2 wrapper
 ***********************************************************************
 * It is exported here because it is used at several places
 **********************************************************************/
typedef struct   hb_libmpeg2_s hb_libmpeg2_t;

hb_libmpeg2_t  * hb_libmpeg2_init();
int              hb_libmpeg2_decode( hb_libmpeg2_t *,
                                      hb_buffer_t * es_buf,
                                      hb_list_t * raw_list );
void             hb_libmpeg2_info( hb_libmpeg2_t * m, int * width,
                                    int * height, int * rate, int * aspect_ratio );
void             hb_libmpeg2_close( hb_libmpeg2_t ** );

/***********************************************************************
 * mpegdemux.c
 **********************************************************************/
int hb_demux_ps( hb_buffer_t * ps_buf, hb_list_t * es_list );

/***********************************************************************
 * dvd.c
 **********************************************************************/
typedef struct hb_dvd_s hb_dvd_t;
typedef struct hb_stream_s hb_stream_t;

hb_dvd_t *   hb_dvd_init( char * path );
int          hb_dvd_title_count( hb_dvd_t * );
hb_title_t * hb_dvd_title_scan( hb_dvd_t *, int title );
int          hb_dvd_start( hb_dvd_t *, int title, int chapter );
void         hb_dvd_stop( hb_dvd_t * );
int          hb_dvd_seek( hb_dvd_t *, float );
int          hb_dvd_read( hb_dvd_t *, hb_buffer_t * );
int          hb_dvd_chapter( hb_dvd_t * );
int          hb_dvd_is_break( hb_dvd_t * d );
void         hb_dvd_close( hb_dvd_t ** );

int         hb_stream_is_stream_type( char * path);
hb_stream_t * hb_stream_open( char * path );
void		 hb_stream_close( hb_stream_t ** );
hb_title_t * hb_stream_title_scan( hb_stream_t *);
int          hb_stream_read( hb_stream_t *, hb_buffer_t *);
int          hb_stream_seek( hb_stream_t *, float );
void		 hb_stream_update_audio( hb_stream_t *, hb_audio_t *);
void		 hb_stream_set_selected_audio_pid_index(hb_stream_t *, int);

/***********************************************************************
 * Work objects
 **********************************************************************/
#define HB_CONFIG_MAX_SIZE 8192
union hb_esconfig_u
{

    struct
    {
        uint8_t bytes[HB_CONFIG_MAX_SIZE];
        int     length;
    } mpeg4;

	struct
	{
	    uint8_t  sps[HB_CONFIG_MAX_SIZE];
	    int       sps_length;
	    uint8_t  pps[HB_CONFIG_MAX_SIZE];
	    int       pps_length;
	} h264;

    struct
    {
        uint8_t bytes[HB_CONFIG_MAX_SIZE];
        int     length;
    } aac;

    struct
    {
        uint8_t headers[3][HB_CONFIG_MAX_SIZE];
        char *language;
    } vorbis;
    
    struct
    {
    	/* ac3flags stores the flags from the AC3 source, as found in scan.c */
    	int  ac3flags;
    } a52;

    struct
    {
    	/* dcaflags stores the flags from the DCA source, as found in scan.c */
    	int  dcaflags;
    } dca;

};

enum
{
    WORK_SYNC = 1,
    WORK_DECMPEG2,
    WORK_DECSUB,
    WORK_RENDER,
    WORK_ENCAVCODEC,
    WORK_ENCXVID,
    WORK_ENCX264,
    WORK_DECA52,
    WORK_DECDCA,
    WORK_DECAVCODEC,
    WORK_DECLPCM,
    WORK_ENCFAAC,
    WORK_ENCLAME,
    WORK_ENCVORBIS
};

enum
{
    FILTER_DEINTERLACE = 1,
    FILTER_DEBLOCK,
    FILTER_DENOISE,
    FILTER_DETELECINE
};

extern hb_work_object_t * hb_objects;

#define HB_WORK_IDLE     0
#define HB_WORK_OK       1
#define HB_WORK_ERROR    2
#define HB_WORK_DONE     3

/***********************************************************************
 * Muxers
 **********************************************************************/
typedef struct hb_mux_object_s hb_mux_object_t;
typedef struct hb_mux_data_s   hb_mux_data_t;

#define HB_MUX_COMMON \
    int (*init)      ( hb_mux_object_t * ); \
    int (*mux)       ( hb_mux_object_t *, hb_mux_data_t *, \
                       hb_buffer_t * ); \
    int (*end)       ( hb_mux_object_t * );

#define DECLARE_MUX( a ) \
    hb_mux_object_t  * hb_mux_##a##_init( hb_job_t * );

DECLARE_MUX( mp4 );
DECLARE_MUX( avi );
DECLARE_MUX( ogm );
DECLARE_MUX( mkv );

