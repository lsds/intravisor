#include ../../../../../config_arm_sim.mak
MAKEFILE := $(shell git rev-parse --show-toplevel)/config_arm.mak
include $(MAKEFILE)


CFLAGS=-fPIC -fPIE -pie -g -O2  -nostdinc -DCVM_MAX_SIZE=$(CONFIG_CVM_MAX_SIZE)\
	-I cheri-libc/include \
	$(TARGET_FLAGS_LINUX) $(SYSROOT_FLAGS_PURE) -B$(CROSS_COMPILE) $(ARCH_PURE) -Iarch/$(TARGET_ARCH)/include\
	-Iunikraft/vfscore/include -Iunikraft/devfs/include -I unikraft/ukswrand/include \
	-I musl-host/src/internal -I musl-host/src/include -I musl-host/include  -I musl-host/arch/morello -I musl-host/src/math \
	-I ffmpeg -DHAVE_AV_CONFIG_H

#CFLAGS_ALL += -D_XOPEN_SOURCE=700 -I$(srcdir)/arch/$(ARCH) -I$(srcdir)/arch/generic -Iobj/src/internal -I$(srcdir)/src/include -I$(srcdir)/src/internal -Iobj/include -I$(srcdir)/include
#	-Wno-unused-command-line-argument -Werror=implicit-function-declaration -Werror=format -Werror=incompatible-pointer-types -Werror=cheri-capability-misuse -Werror=cheri-bitwise-operations -Werror=cheri-prototypes -Werror=pass-failed -Werror=undefined-internal -Wno-error=cheri-capability-misuse \

ifneq ($(MODE),sim)
endif

DEPS = 
OBJDIR = obj
SRC = main.c tramps.c hostcalls.c nolibc_printf2.c nolibc_float.c nolibc_printf.c nolibc_file.c  nolibc_strings.c nolibc_math.c nolibc_time.c nolibc_unsorted.c nolibc_regex.c dlmalloc_nonreuse.c cpio.c nolibc_network.c
SRC += $(wildcard musl-host/src/ctype/*.c)
SRC += $(wildcard musl-host/src/locale/*.c)
SRC += $(wildcard musl-host/src/termios/*.c)
SRC += $(wildcard musl-host/src/complex/*.c)
SRC += $(wildcard musl-host/src/fenv/*.c)
SRC += $(wildcard musl-host/src/math/*.c)
SRC += $(wildcard musl-host/src/string/*.c)
SRC += $(wildcard musl-host/src/stdlib/*.c)
SRC += $(wildcard musl-host/src/internal/*.c)
SRC += $(wildcard musl-host/src/stdio/*.c)
SRC += $(wildcard musl-host/src/multibyte/*.c)
SRC += $(wildcard musl-host/src/errno/*.c)
SRC += unikraft/vfscore/main.c unikraft/vfscore/fd.c unikraft/vfscore/rootfs.c unikraft/vfscore/task.c unikraft/vfscore/vnode.c  unikraft/vfscore/dentry.c unikraft/vfscore/file.c unikraft/vfscore/subr_uio.c unikraft/vfscore/fops.c unikraft/vfscore/lookup.c unikraft/vfscore/mount.c unikraft/vfscore/syscalls.c
SRC += unikraft/ramfs/ramfs_vnops.c unikraft/ramfs/ramfs_vfsops.c 
SRC += unikraft/devfs/devfs_vnops.c unikraft/devfs/device.c unikraft/devfs/null.c
SRC += unikraft/ukswrand/dev.c unikraft/ukswrand/swrand.c unikraft/ukswrand/mwc.c
#full libswresample
SRC += ffmpeg/libswresample/audioconvert.c ffmpeg/libswresample/version.c ffmpeg/libswresample/dither.c ffmpeg/libswresample/options.c ffmpeg/libswresample/rematrix.c ffmpeg/libswresample/resample.c ffmpeg/libswresample/resample_dsp.c ffmpeg/libswresample/swresample.c ffmpeg/libswresample/swresample_frame.c
#full libavutils
SRC +=  ffmpeg/libavutil/dovi_meta.c  ffmpeg/libavutil/version.c ffmpeg/libavutil/video_enc_params.c ffmpeg/libavutil/film_grain_params.c ffmpeg/libavutil/hdr_dynamic_vivid_metadata.c ffmpeg/libavutil/hdr_dynamic_metadata.c ffmpeg/libavutil/csp.c ffmpeg/libavutil/avsscanf.c ffmpeg/libavutil/adler32.c ffmpeg/libavutil/aes.c ffmpeg/libavutil/aes_ctr.c ffmpeg/libavutil/audio_fifo.c ffmpeg/libavutil/avstring.c ffmpeg/libavutil/base64.c ffmpeg/libavutil/blowfish.c ffmpeg/libavutil/bprint.c ffmpeg/libavutil/buffer.c ffmpeg/libavutil/cast5.c ffmpeg/libavutil/camellia.c ffmpeg/libavutil/channel_layout.c ffmpeg/libavutil/color_utils.c ffmpeg/libavutil/cpu.c ffmpeg/libavutil/crc.c ffmpeg/libavutil/des.c ffmpeg/libavutil/dict.c ffmpeg/libavutil/display.c ffmpeg/libavutil/downmix_info.c ffmpeg/libavutil/error.c ffmpeg/libavutil/eval.c ffmpeg/libavutil/fifo.c ffmpeg/libavutil/file.c ffmpeg/libavutil/file_open.c  ffmpeg/libavutil/float_dsp.c ffmpeg/libavutil/fixed_dsp.c ffmpeg/libavutil/frame.c ffmpeg/libavutil/hash.c ffmpeg/libavutil/hmac.c ffmpeg/libavutil/hwcontext.c ffmpeg/libavutil/imgutils.c ffmpeg/libavutil/integer.c ffmpeg/libavutil/intmath.c ffmpeg/libavutil/lfg.c ffmpeg/libavutil/lls.c ffmpeg/libavutil/log.c ffmpeg/libavutil/log2_tab.c ffmpeg/libavutil/mathematics.c ffmpeg/libavutil/mastering_display_metadata.c ffmpeg/libavutil/md5.c ffmpeg/libavutil/mem.c ffmpeg/libavutil/murmur3.c ffmpeg/libavutil/opt.c ffmpeg/libavutil/parseutils.c ffmpeg/libavutil/pixdesc.c ffmpeg/libavutil/pixelutils.c ffmpeg/libavutil/random_seed.c ffmpeg/libavutil/rational.c ffmpeg/libavutil/reverse.c ffmpeg/libavutil/rc4.c ffmpeg/libavutil/ripemd.c ffmpeg/libavutil/samplefmt.c ffmpeg/libavutil/sha.c ffmpeg/libavutil/sha512.c ffmpeg/libavutil/slicethread.c ffmpeg/libavutil/spherical.c ffmpeg/libavutil/stereo3d.c ffmpeg/libavutil/threadmessage.c ffmpeg/libavutil/time.c ffmpeg/libavutil/timecode.c ffmpeg/libavutil/tree.c ffmpeg/libavutil/twofish.c ffmpeg/libavutil/utils.c ffmpeg/libavutil/xga_font_data.c ffmpeg/libavutil/xtea.c ffmpeg/libavutil/tea.c
#default libavfilter
SRC += ffmpeg/libavfilter/allfilters.c ffmpeg/libavfilter/audio.c ffmpeg/libavfilter/avfilter.c ffmpeg/libavfilter/avfiltergraph.c ffmpeg/libavfilter/buffersink.c ffmpeg/libavfilter/buffersrc.c ffmpeg/libavfilter/drawutils.c ffmpeg/libavfilter/fifo.c ffmpeg/libavfilter/formats.c ffmpeg/libavfilter/framepool.c ffmpeg/libavfilter/framequeue.c ffmpeg/libavfilter/graphdump.c ffmpeg/libavfilter/graphparser.c ffmpeg/libavfilter/transform.c ffmpeg/libavfilter/video.c
#full libswscale
SRC +=  ffmpeg/libswscale/alphablend.c ffmpeg/libswscale/hscale.c ffmpeg/libswscale/hscale_fast_bilinear.c ffmpeg/libswscale/gamma.c ffmpeg/libswscale/half2float.c ffmpeg/libswscale/input.c ffmpeg/libswscale/options.c ffmpeg/libswscale/output.c ffmpeg/libswscale/rgb2rgb.c ffmpeg/libswscale/slice.c ffmpeg/libswscale/swscale.c ffmpeg/libswscale/swscale_unscaled.c ffmpeg/libswscale/utils.c ffmpeg/libswscale/version.c ffmpeg/libswscale/yuv2rgb.c ffmpeg/libswscale/vscale.c

###########
SRC += ffmpeg/libavcodec/audiodsp.c ffmpeg/libavcodec/ac3dsp.c
SRC += ffmpeg/libavcodec/rdft.c ffmpeg/libavcodec/dct.c ffmpeg/libavcodec/dct32_fixed.c ffmpeg/libavcodec/dct32_float.c ffmpeg/libavcodec/dctref.c ffmpeg/libavcodec/cbrt_data.c ffmpeg/libavcodec/cbrt_data_fixed.c ffmpeg/libavcodec/pcm-blurayenc.c ffmpeg/libavcodec/pcm-bluray.c ffmpeg/libavcodec/pcm-dvd.c ffmpeg/libavcodec/pcm-dvdenc.c
SRC += ffmpeg/libavcodec/eac3_core_bsf.c ffmpeg/libavcodec/eac3_data.c ffmpeg/libavcodec/eac3dec.c ffmpeg/libavcodec/ac3enc_fixed.c ffmpeg/libavcodec/ac3dec.c
SRC += ffmpeg/libavformat/ac3dec.c ffmpeg/libavformat/apetag.c  ffmpeg/libavformat/ape.c ffmpeg/libavformat/aacdec.c ffmpeg/libavformat/av1.c ffmpeg/libavformat/ip.c ffmpeg/libavformat/asf_tags.c ffmpeg/libavformat/rtpenc_rfc4175.c ffmpeg/libavformat/version.c ffmpeg/libavformat/demux.c ffmpeg/libavformat/avformat.c ffmpeg/libavformat/rawutils.c ffmpeg/libavformat/movenchint.c ffmpeg/libavformat/vpcc.c ffmpeg/libavformat/rtpdec_xiph.c ffmpeg/libavformat/rtpdec_mpeg12.c ffmpeg/libavformat/rmsipr.c ffmpeg/libavformat/rm.c ffmpeg/libavformat/isom.c ffmpeg/libavformat/rtpenc_mpegts.c ffmpeg/libavformat/rtpenc_amr.c ffmpeg/libavformat/rtpenc_h263_rfc2190.c ffmpeg/libavformat/rtpenc_xiph.c ffmpeg/libavformat/rtpenc_vp9.c ffmpeg/libavformat/rtpenc_h263.c ffmpeg/libavformat/rtpenc_latm.c ffmpeg/libavformat/rtpenc_vp8.c ffmpeg/libavformat/rtpenc_h264_hevc.c ffmpeg/libavformat/rtpenc_vc2hq.c ffmpeg/libavformat/rtpenc_jpeg.c ffmpeg/libavformat/rtpenc_aac.c ffmpeg/libavformat/rtpenc_h261.c ffmpeg/libavformat/rtpenc_mpv.c ffmpeg/libavformat/rmdec.c ffmpeg/libavformat/asf.c ffmpeg/libavformat/mpegts.c ffmpeg/libavformat/hevc.c ffmpeg/libavformat/rtpenc.c ffmpeg/libavformat/avc.c ffmpeg/libavformat/rdt.c ffmpeg/libavformat/rtpdec_asf.c ffmpeg/libavformat/rtpdec.c ffmpeg/libavformat/rtp.c ffmpeg/libavformat/rtpenc_chain.c ffmpeg/libavformat/urldecode.c ffmpeg/libavformat/httpauth.c ffmpeg/libavformat/http.c ffmpeg/libavformat/udp.c ffmpeg/libavformat/rtspenc.c ffmpeg/libavformat/rtsp.c ffmpeg/libavformat/rtpproto.c ffmpeg/libavformat/mux.c ffmpeg/libavformat/network.c ffmpeg/libavformat/os_support.c ffmpeg/libavformat/sdp.c ffmpeg/libavformat/allformats.c ffmpeg/libavformat/options.c ffmpeg/libavformat/utils.c ffmpeg/libavformat/aviobuf.c ffmpeg/libavformat/format.c ffmpeg/libavformat/avio.c ffmpeg/libavformat/protocols.c ffmpeg/libavformat/file.c ffmpeg/libavformat/url.c ffmpeg/libavformat/id3v2.c ffmpeg/libavformat/id3v1.c
SRC +=  ffmpeg/libavcodec/ac3.c ffmpeg/libavcodec/ac3enc.c ffmpeg/libavcodec/eac3enc.c ffmpeg/libavcodec/ac3enc_float.c ffmpeg/libavcodec/aac_ac3_parser.c ffmpeg/libavcodec/ac3_channel_layout_tab.c ffmpeg/libavcodec/ac3tab.c ffmpeg/libavcodec/aacps_common.c ffmpeg/libavcodec/adts_header.c ffmpeg/libavcodec/ac3_parser.c ffmpeg/libavcodec/speedhq.c ffmpeg/libavcodec/get_buffer.c ffmpeg/libavcodec/parsers.c ffmpeg/libavcodec/mpeg4audio_sample_rates.c ffmpeg/libavcodec/to_upper4.c ffmpeg/libavcodec/version.c ffmpeg/libavcodec/snow.c ffmpeg/libavcodec/speedhqenc.c ffmpeg/libavcodec/h274.c ffmpeg/libavcodec/atsc_a53.c ffmpeg/libavcodec/flacencdsp.c ffmpeg/libavcodec/dynamic_hdr_vivid.c ffmpeg/libavcodec/dynamic_hdr10_plus.c ffmpeg/libavcodec/dovi_rpu.c ffmpeg/libavcodec/codec_par.c ffmpeg/libavcodec/golomb.c ffmpeg/libavcodec/bitstream.c ffmpeg/libavcodec/mpeg4audio.c ffmpeg/libavcodec/xiph.c ffmpeg/libavcodec/options.c ffmpeg/libavcodec/raw.c ffmpeg/libavcodec/utils.c ffmpeg/libavcodec/bsf.c  ffmpeg/libavcodec/avpacket.c ffmpeg/libavcodec/decode.c ffmpeg/libavcodec/allcodecs.c ffmpeg/libavcodec/parser.c  ffmpeg/libavcodec/bitstream_filters.c ffmpeg/libavcodec/codec_desc.c 
SRC += ffmpeg/libavcodec/avcodec.c ffmpeg/libavcodec/jpegtables.c ffmpeg/libavcodec/null_bsf.c
SRC += ffmpeg/libavformat/movenc_ttml.c ffmpeg/libavformat/dovi_isom.c ffmpeg/libavformat/isom_tags.c ffmpeg/libavformat/seek.c ffmpeg/libavformat/metadata.c ffmpeg/libavformat/movenccenc.c ffmpeg/libavformat/wavenc.c ffmpeg/libavformat/wavdec.c 
SRC += ffmpeg/libavformat/mov_chan.c ffmpeg/libavformat/movenc.c ffmpeg/libavformat/dump.c ffmpeg/libavformat/riffenc.c ffmpeg/libavformat/riff.c ffmpeg/libavformat/riffdec.c ffmpeg/libavformat/pcm.c ffmpeg/libavformat/pcmdec.c ffmpeg/libavformat/pcmenc.c
SRC += ffmpeg/libavcodec/pcm.c ffmpeg/libavcodec/encode.c
#img2
SRC += ffmpeg/libavformat/img2.c ffmpeg/libavformat/img2_alias_pix.c ffmpeg/libavformat/img2_brender_pix.c ffmpeg/libavformat/img2dec.c ffmpeg/libavformat/img2enc.c
#aac:
SRC +=  ffmpeg/libavcodec/latm_parser.c ffmpeg/libavcodec/aac_adtstoasc_bsf.c ffmpeg/libavcodec/aac_parser.c ffmpeg/libavcodec/aacpsdsp_float.c ffmpeg/libavcodec/sbrdsp.c ffmpeg/libavcodec/aacps.c ffmpeg/libavcodec/mdct15.c  ffmpeg/libavcodec/aacsbr.c ffmpeg/libavcodec/profiles.c ffmpeg/libavcodec/imgconvert.c ffmpeg/libavcodec/aacenc.c ffmpeg/libavcodec/aacdec.c ffmpeg/libavcodec/aaccoder.c ffmpeg/libavcodec/audio_frame_queue.c ffmpeg/libavcodec/aactab.c ffmpeg/libavcodec/aacenc_ltp.c ffmpeg/libavcodec/aacenc_pred.c ffmpeg/libavcodec/aacenc_is.c ffmpeg/libavcodec/aacenc_tns.c ffmpeg/libavcodec/lpc.c ffmpeg/libavcodec/sinewin.c ffmpeg/libavcodec/psymodel.c ffmpeg/libavcodec/iirfilter.c ffmpeg/libavcodec/aacpsy.c ffmpeg/libavcodec/aacenctab.c ffmpeg/libavcodec/kbdwin.c  ffmpeg/libavcodec/mdct_float.c ffmpeg/libavcodec/mdct_fixed_32.c ffmpeg/libavcodec/fft_float.c ffmpeg/libavcodec/fft_fixed_32.c ffmpeg/libavcodec/fft_init_table.c
#ffmpeg
SRC +=  ffmpeg/fftools/ffmpeg_mux.c ffmpeg/fftools/opt_common.c ffmpeg/fftools/ffmpeg.c ffmpeg/fftools/cmdutils.c ffmpeg/fftools/ffmpeg_opt.c ffmpeg/fftools/ffmpeg_filter.c ffmpeg/fftools/ffmpeg_hw.c
##video
SRC += ffmpeg/libavcodec/rawdec.c ffmpeg/libavcodec/rawenc.c ffmpeg/libavcodec/bswapdsp.c
SRC += ffmpeg/libavformat/rawenc.c ffmpeg/libavformat/rawdec.c ffmpeg/libavformat/rawvideodec.c
SRC += ffmpeg/libavfilter/vf_framerate.c ffmpeg/libavfilter/src_movie.c
#avi
SRC += ffmpeg/libavformat/avienc.c ffmpeg/libavformat/avidec.c ffmpeg/libavformat/avlanguage.c ffmpeg/libavformat/mpegtsenc.c
SRC += ffmpeg/libavcodec/exif.c ffmpeg/libavcodec/tiff_common.c ffmpeg/libavcodec/tiff.c ffmpeg/libavcodec/lzw.c ffmpeg/libavcodec/faxcompr.c
#mpegaudio
SRC += ffmpeg/libavcodec/mpegaudio.c ffmpeg/libavcodec/mpegaudiodec_common.c ffmpeg/libavcodec/mpegaudiodec_float.c ffmpeg/libavcodec/mpegaudiodsp.c ffmpeg/libavcodec/mpegaudiodsp_fixed.c ffmpeg/libavcodec/mpegaudioenc_fixed.c ffmpeg/libavcodec/mpegaudiotabs.c ffmpeg/libavcodec/mpegaudio_parser.c ffmpeg/libavcodec/mpegaudiodata.c ffmpeg/libavcodec/mpegaudiodec_fixed.c ffmpeg/libavcodec/mpegaudiodecheader.c ffmpeg/libavcodec/mpegaudiodsp_data.c ffmpeg/libavcodec/mpegaudiodsp_float.c ffmpeg/libavcodec/mpegaudioenc_float.c
#mpeg4
SRC += ffmpeg/libavcodec/snow_dwt.c ffmpeg/libavcodec/mpegvideo_dec.c  ffmpeg/libavcodec/msmpeg4.c ffmpeg/libavcodec/msmpeg4data.c ffmpeg/libavcodec/msmpeg4dec.c ffmpeg/libavcodec/msmpeg4enc.c ffmpeg/libavcodec/mpeg12.c ffmpeg/libavcodec/mpeg12dec.c ffmpeg/libavcodec/mpeg12framerate.c ffmpeg/libavcodec/mpeg12data.c ffmpeg/libavcodec/mpeg12enc.c ffmpeg/libavcodec/mpegvideo_parser.c ffmpeg/libavcodec/mpeg4videoenc.c ffmpeg/libavcodec/mpeg4videodec.c ffmpeg/libavcodec/ituh263enc.c ffmpeg/libavcodec/mathtables.c ffmpeg/libavcodec/mpegvideodata.c ffmpeg/libavcodec/mpegvideo_enc.c ffmpeg/libavcodec/mpegvideo.c ffmpeg/libavcodec/mpegutils.c ffmpeg/libavcodec/mpeg_er.c ffmpeg/libavcodec/error_resilience.c ffmpeg/libavcodec/videodsp.c ffmpeg/libavcodec/mpegvideodsp.c ffmpeg/libavcodec/hpeldsp.c ffmpeg/libavcodec/h264chroma.c ffmpeg/libavcodec/blockdsp.c ffmpeg/libavcodec/idctdsp.c ffmpeg/libavcodec/simple_idct.c ffmpeg/libavcodec/jrevdct.c ffmpeg/libavcodec/xvididct.c ffmpeg/libavcodec/mpegpicture.c ffmpeg/libavcodec/mpegvideo_motion.c ffmpeg/libavcodec/mpeg4video.c ffmpeg/libavcodec/me_cmp.c ffmpeg/libavcodec/motion_est.c ffmpeg/libavcodec/ratecontrol.c ffmpeg/libavcodec/qpeldsp.c ffmpeg/libavcodec/pixblockdsp.c ffmpeg/libavcodec/mpegvideoencdsp.c ffmpeg/libavcodec/fdctdsp.c ffmpeg/libavcodec/jfdctint.c ffmpeg/libavcodec/jfdctfst.c ffmpeg/libavcodec/aandcttab.c ffmpeg/libavcodec/ituh263dec.c  ffmpeg/libavcodec/mpeg4video_parser.c ffmpeg/libavcodec/rl.c
SRC += ffmpeg/libavformat/nullenc.c ffmpeg/libavformat/mpegvideodec.c
#mpegts
SRC += 
#h263
SRC += ffmpeg/libavcodec/yuv4dec.c ffmpeg/libavcodec/yuv4enc.c ffmpeg/libavcodec/h263dec.c ffmpeg/libavcodec/h263data.c ffmpeg/libavcodec/h263dsp.c ffmpeg/libavcodec/h263_parser.c ffmpeg/libavcodec/h263.c ffmpeg/libavcodec/flvenc.c
SRC += ffmpeg/libavformat/h263dec.c
#h264
SRC +=  ffmpeg/libavcodec/h264dec.c ffmpeg/libavcodec/h264_cabac.c ffmpeg/libavcodec/h264_cavlc.c ffmpeg/libavcodec/h264_direct.c ffmpeg/libavcodec/h264_loopfilter.c ffmpeg/libavcodec/h264_mb.c ffmpeg/libavcodec/h264_picture.c ffmpeg/libavcodec/h264_refs.c ffmpeg/libavcodec/h264_sei.c ffmpeg/libavcodec/h264_slice.c ffmpeg/libavcodec/h264data.c ffmpeg/libavcodec/h264_parse.c ffmpeg/libavcodec/h264pred.c ffmpeg/libavcodec/h264dsp.c ffmpeg/libavcodec/h264qpel.c ffmpeg/libavcodec/startcode.c ffmpeg/libavcodec/h264idct.c ffmpeg/libavcodec/h264_ps.c ffmpeg/libavcodec/h264_parser.c
#flac
SRC += ffmpeg/libavcodec/flacdata.c ffmpeg/libavcodec/flac.c ffmpeg/libavcodec/flac_parser.c ffmpeg/libavcodec/flacdec.c ffmpeg/libavcodec/flacdsp.c ffmpeg/libavcodec/flacenc.c
SRC += ffmpeg/libavformat/flacenc.c ffmpeg/libavformat/flacdec.c ffmpeg/libavformat/oggparsevorbis.c ffmpeg/libavformat/flac_picture.c ffmpeg/libavformat/replaygain.c ffmpeg/libavformat/flacenc_header.c
#HEVC
SRC += ffmpeg/libavcodec/flvdec.c ffmpeg/libavcodec/cabac.c ffmpeg/libavcodec/hevc_parser.c ffmpeg/libavcodec/hevc_parse.c  ffmpeg/libavcodec/h2645_parse.c ffmpeg/libavcodec/hevc_ps.c ffmpeg/libavcodec/hevc_sei.c  ffmpeg/libavcodec/hevcdec.c ffmpeg/libavcodec/hevc_mvs.c ffmpeg/libavcodec/hevc_cabac.c  ffmpeg/libavcodec/hevc_refs.c ffmpeg/libavcodec/hevcpred.c ffmpeg/libavcodec/hevcdsp.c  ffmpeg/libavcodec/hevc_filter.c  ffmpeg/libavcodec/hevc_data.c  ffmpeg/libavcodec/mediacodecdec.c
SRC += ffmpeg/libavformat/flvdec.c ffmpeg/libavformat/flvenc.c ffmpeg/libavformat/hevcdec.c
#vorbis
SRC += ffmpeg/libavcodec/vlc.c ffmpeg/libavcodec/vorbis.c ffmpeg/libavcodec/vorbisenc.c ffmpeg/libavcodec/vorbisdec.c ffmpeg/libavcodec/vorbis_parser.c ffmpeg/libavcodec/vorbisdsp.c ffmpeg/libavcodec/vorbis_data.c
SRC += ffmpeg/libavformat/vorbiscomment.c 	ffmpeg/libavformat/mux_utils.c 	ffmpeg/libavformat/demux_utils.c
#networking
SRC += ffmpeg/libavformat/tcp.c
#video filters
SRC += ffmpeg/libavcodec/avdct.c
SRC += ffmpeg/libavfilter/version.c ffmpeg/libavfilter/bbox.c \
	ffmpeg/libavfilter/colorspacedsp.c \
	ffmpeg/libavfilter/f_bench.c \
	ffmpeg/libavfilter/f_drawgraph.c \
	ffmpeg/libavfilter/f_interleave.c \
	ffmpeg/libavfilter/f_loop.c \
	ffmpeg/libavfilter/f_metadata.c \
	ffmpeg/libavfilter/f_perms.c \
	ffmpeg/libavfilter/f_realtime.c \
	ffmpeg/libavfilter/f_reverse.c \
	ffmpeg/libavfilter/f_select.c \
	ffmpeg/libavfilter/f_sendcmd.c \
	ffmpeg/libavfilter/f_sidedata.c \
	ffmpeg/libavfilter/f_streamselect.c \
	ffmpeg/libavfilter/framesync.c \
	ffmpeg/libavfilter/lavfutils.c \
	ffmpeg/libavfilter/motion_estimation.c \
	ffmpeg/libavfilter/scale_eval.c \
	ffmpeg/libavfilter/setpts.c \
	ffmpeg/libavfilter/settb.c \
	ffmpeg/libavfilter/split.c \
	ffmpeg/libavfilter/trim.c \
	ffmpeg/libavfilter/vf_alphamerge.c \
	ffmpeg/libavfilter/vf_aspect.c \
	ffmpeg/libavfilter/vf_atadenoise.c \
	ffmpeg/libavfilter/vf_avgblur.c \
	ffmpeg/libavfilter/vf_bbox.c \
	ffmpeg/libavfilter/vf_bitplanenoise.c \
	ffmpeg/libavfilter/vf_blackdetect.c \
	ffmpeg/libavfilter/vf_blackframe.c \
	ffmpeg/libavfilter/vf_blend.c \
	ffmpeg/libavfilter/vf_boxblur.c \
	ffmpeg/libavfilter/vf_bwdif.c \
	ffmpeg/libavfilter/vf_chromakey.c \
	ffmpeg/libavfilter/vf_ciescope.c \
	ffmpeg/libavfilter/vf_codecview.c \
	ffmpeg/libavfilter/vf_colorbalance.c \
	ffmpeg/libavfilter/vf_colorchannelmixer.c \
	ffmpeg/libavfilter/vf_colorkey.c \
	ffmpeg/libavfilter/vf_colorlevels.c \
	ffmpeg/libavfilter/vf_colormatrix.c \
	ffmpeg/libavfilter/vf_colorspace.c \
	ffmpeg/libavfilter/vf_copy.c \
	ffmpeg/libavfilter/vf_convolution.c \
	ffmpeg/libavfilter/vf_cover_rect.c \
	ffmpeg/libavfilter/vf_crop.c \
	ffmpeg/libavfilter/vf_cropdetect.c \
	ffmpeg/libavfilter/vf_curves.c \
	ffmpeg/libavfilter/vf_datascope.c \
	ffmpeg/libavfilter/vf_dctdnoiz.c \
	ffmpeg/libavfilter/vf_deband.c \
	ffmpeg/libavfilter/vf_decimate.c \
	ffmpeg/libavfilter/vf_deflicker.c \
	ffmpeg/libavfilter/vf_dejudder.c \
	ffmpeg/libavfilter/vf_delogo.c \
	ffmpeg/libavfilter/vf_deshake.c \
	ffmpeg/libavfilter/vf_despill.c \
	ffmpeg/libavfilter/vf_detelecine.c \
	ffmpeg/libavfilter/vf_displace.c \
	ffmpeg/libavfilter/vf_drawbox.c \
	ffmpeg/libavfilter/vf_edgedetect.c \
	ffmpeg/libavfilter/vf_eq.c \
	ffmpeg/libavfilter/vf_extractplanes.c \
	ffmpeg/libavfilter/vf_fade.c \
	ffmpeg/libavfilter/vf_field.c \
	ffmpeg/libavfilter/vf_fieldmatch.c \
	ffmpeg/libavfilter/vf_fieldorder.c \
	ffmpeg/libavfilter/vf_find_rect.c \
	ffmpeg/libavfilter/vf_floodfill.c \
	ffmpeg/libavfilter/vf_format.c \
	ffmpeg/libavfilter/vf_framestep.c \
	ffmpeg/libavfilter/vf_fps.c \
	ffmpeg/libavfilter/vf_framepack.c \
	ffmpeg/libavfilter/vf_fspp.c \
	ffmpeg/libavfilter/vf_hue.c \
	ffmpeg/libavfilter/vf_gblur.c \
	ffmpeg/libavfilter/vf_geq.c \
	ffmpeg/libavfilter/vf_gradfun.c \
	ffmpeg/libavfilter/vf_hflip.c \
	ffmpeg/libavfilter/vf_histeq.c \
	ffmpeg/libavfilter/vf_histogram.c \
	ffmpeg/libavfilter/vf_hqdn3d.c \
	ffmpeg/libavfilter/vf_hqx.c \
	ffmpeg/libavfilter/vf_hwmap.c \
	ffmpeg/libavfilter/vf_hwupload.c \
	ffmpeg/libavfilter/vf_hwdownload.c \
	ffmpeg/libavfilter/vf_hysteresis.c \
	ffmpeg/libavfilter/vf_idet.c \
	ffmpeg/libavfilter/vf_il.c \
	ffmpeg/libavfilter/vf_kerndeint.c \
	ffmpeg/libavfilter/vf_lenscorrection.c \
	ffmpeg/libavfilter/vf_limiter.c \
	ffmpeg/libavfilter/vf_lumakey.c \
	ffmpeg/libavfilter/vf_lut.c \
	ffmpeg/libavfilter/vf_lut2.c \
	ffmpeg/libavfilter/vf_maskedclamp.c \
	ffmpeg/libavfilter/vf_maskedmerge.c \
	ffmpeg/libavfilter/vf_mergeplanes.c \
	ffmpeg/libavfilter/vf_mestimate.c \
	ffmpeg/libavfilter/vf_midequalizer.c \
	ffmpeg/libavfilter/vf_minterpolate.c \
	ffmpeg/libavfilter/vf_mpdecimate.c \
	ffmpeg/libavfilter/vf_neighbor.c \
	ffmpeg/libavfilter/vf_nlmeans.c \
	ffmpeg/libavfilter/vf_noise.c \
	ffmpeg/libavfilter/vf_null.c \
	ffmpeg/libavfilter/vf_overlay.c \
	ffmpeg/libavfilter/vf_owdenoise.c \
	ffmpeg/libavfilter/vf_pad.c \
	ffmpeg/libavfilter/vf_palettegen.c \
	ffmpeg/libavfilter/vf_paletteuse.c \
	ffmpeg/libavfilter/vf_perspective.c \
	ffmpeg/libavfilter/vf_phase.c \
	ffmpeg/libavfilter/vf_pixdesctest.c \
	ffmpeg/libavfilter/vf_premultiply.c \
	ffmpeg/libavfilter/vf_pseudocolor.c \
	ffmpeg/libavfilter/vf_psnr.c \
	ffmpeg/libavfilter/vf_pullup.c \
	ffmpeg/libavfilter/vf_qp.c \
	ffmpeg/libavfilter/vf_random.c \
	ffmpeg/libavfilter/vf_readeia608.c \
	ffmpeg/libavfilter/vf_readvitc.c \
	ffmpeg/libavfilter/vf_remap.c \
	ffmpeg/libavfilter/vf_removegrain.c \
	ffmpeg/libavfilter/vf_repeatfields.c \
	ffmpeg/libavfilter/vf_rotate.c \
	ffmpeg/libavfilter/vf_sab.c \
	ffmpeg/libavfilter/vf_scale.c \
	ffmpeg/libavfilter/vf_selectivecolor.c \
	ffmpeg/libavfilter/vf_separatefields.c \
	ffmpeg/libavfilter/vf_showinfo.c \
	ffmpeg/libavfilter/vf_showpalette.c \
	ffmpeg/libavfilter/vf_shuffleframes.c \
	ffmpeg/libavfilter/vf_shuffleplanes.c \
	ffmpeg/libavfilter/vf_signalstats.c \
	ffmpeg/libavfilter/vf_signature.c \
	ffmpeg/libavfilter/vf_smartblur.c \
	ffmpeg/libavfilter/vf_spp.c \
	ffmpeg/libavfilter/vf_ssim.c \
	ffmpeg/libavfilter/vf_stack.c \
	ffmpeg/libavfilter/vf_stereo3d.c \
	ffmpeg/libavfilter/vf_super2xsai.c \
	ffmpeg/libavfilter/vf_swaprect.c \
	ffmpeg/libavfilter/vf_swapuv.c \
	ffmpeg/libavfilter/vf_telecine.c \
	ffmpeg/libavfilter/vf_threshold.c \
	ffmpeg/libavfilter/vf_thumbnail.c \
	ffmpeg/libavfilter/vf_tile.c \
	ffmpeg/libavfilter/vf_tinterlace.c \
	ffmpeg/libavfilter/vf_tonemap.c \
	ffmpeg/libavfilter/vf_transpose.c \
	ffmpeg/libavfilter/vf_unsharp.c \
	ffmpeg/libavfilter/vf_vaguedenoiser.c \
	ffmpeg/libavfilter/vf_vectorscope.c \
	ffmpeg/libavfilter/vf_vflip.c \
	ffmpeg/libavfilter/vf_vignette.c \
	ffmpeg/libavfilter/vf_vmafmotion.c \
	ffmpeg/libavfilter/vf_w3fdif.c \
	ffmpeg/libavfilter/vf_waveform.c \
	ffmpeg/libavfilter/vf_weave.c \
	ffmpeg/libavfilter/vf_xbr.c \
	ffmpeg/libavfilter/vf_yadif.c \
	ffmpeg/libavfilter/edge_common.c \
	ffmpeg/libavfilter/qp_table.c \
	ffmpeg/libavfilter/boxblur.c \
	ffmpeg/libavfilter/colorspace.c \
	ffmpeg/libavfilter/yadif_common.c \
	ffmpeg/libavfilter/vf_zoompan.c \
	ffmpeg/libavfilter/vsrc_cellauto.c \
	ffmpeg/libavfilter/vsrc_life.c \
	ffmpeg/libavfilter/vsrc_mandelbrot.c \
	ffmpeg/libavfilter/vsrc_mptestsrc.c \
	ffmpeg/libavfilter/vsrc_testsrc.c \
	ffmpeg/libavfilter/scene_sad.c 

#	ffmpeg/libavfilter/vf_lut3d.c \
#	ffmpeg/libavfilter/vf_fieldhint.c \

SRC	+=	ffmpeg/libavfilter/af_acopy.c \
	ffmpeg/libavfilter/af_aformat.c \
	ffmpeg/libavfilter/af_amerge.c \
	ffmpeg/libavfilter/af_anull.c \
	ffmpeg/libavfilter/af_apad.c \
	ffmpeg/libavfilter/af_aresample.c \
	ffmpeg/libavfilter/asrc_anullsrc.c \
	ffmpeg/libavfilter/asink_anullsink.c \
	ffmpeg/libavfilter/vsink_nullsink.c \
	ffmpeg/libavfilter/avf_concat.c

#	ffmpeg/libavformat/concat.c

#	ffmpeg/libavfilter/vf_fftfilt.c 
#	ffmpeg/libavfilter/vf_convolve.c \
#	ffmpeg/libavfilter/vf_elbg.c \

####### OLD 
#SRC += ffmpeg/libavdevice/alldevices.c ffmpeg/libavdevice/avdevice.c ffmpeg/libavdevice/lavfi.c ffmpeg/libavdevice/utils.c
#SRC += ffmpeg/libavfilter/allfilters.c ffmpeg/libavfilter/audio.c ffmpeg/libavfilter/avfilter.c ffmpeg/libavfilter/avfiltergraph.c ffmpeg/libavfilter/buffersink.c ffmpeg/libavfilter/buffersrc.c ffmpeg/libavfilter/drawutils.c ffmpeg/libavfilter/fifo.c ffmpeg/libavfilter/formats.c ffmpeg/libavfilter/framepool.c ffmpeg/libavfilter/framequeue.c ffmpeg/libavfilter/graphdump.c ffmpeg/libavfilter/graphparser.c ffmpeg/libavfilter/opencl_allkernels.c ffmpeg/libavfilter/transform.c ffmpeg/libavfilter/video.c
#SRC += ffmpeg/libavformat/3dostr.c ffmpeg/libavformat/4xm.c ffmpeg/libavformat/a64.c ffmpeg/libavformat/aacdec.c ffmpeg/libavformat/aadec.c ffmpeg/libavformat/ac3dec.c ffmpeg/libavformat/acm.c ffmpeg/libavformat/act.c ffmpeg/libavformat/adp.c ffmpeg/libavformat/ads.c ffmpeg/libavformat/adtsenc.c ffmpeg/libavformat/adxdec.c ffmpeg/libavformat/aea.c ffmpeg/libavformat/afc.c ffmpeg/libavformat/aiffdec.c ffmpeg/libavformat/aiffenc.c ffmpeg/libavformat/aixdec.c ffmpeg/libavformat/allformats.c ffmpeg/libavformat/amr.c ffmpeg/libavformat/anm.c ffmpeg/libavformat/apc.c ffmpeg/libavformat/ape.c ffmpeg/libavformat/apetag.c ffmpeg/libavformat/apngdec.c ffmpeg/libavformat/apngenc.c ffmpeg/libavformat/aqtitledec.c ffmpeg/libavformat/asf.c ffmpeg/libavformat/asfcrypt.c ffmpeg/libavformat/asfdec_f.c ffmpeg/libavformat/asfdec_o.c ffmpeg/libavformat/asfenc.c ffmpeg/libavformat/assdec.c ffmpeg/libavformat/assenc.c ffmpeg/libavformat/ast.c ffmpeg/libavformat/astdec.c ffmpeg/libavformat/astenc.c ffmpeg/libavformat/au.c ffmpeg/libavformat/audiointerleave.c ffmpeg/libavformat/avc.c ffmpeg/libavformat/avidec.c ffmpeg/libavformat/avienc.c ffmpeg/libavformat/avio.c ffmpeg/libavformat/aviobuf.c ffmpeg/libavformat/avlanguage.c ffmpeg/libavformat/avr.c ffmpeg/libavformat/avs.c ffmpeg/libavformat/bethsoftvid.c ffmpeg/libavformat/bfi.c ffmpeg/libavformat/bink.c ffmpeg/libavformat/bintext.c ffmpeg/libavformat/bit.c ffmpeg/libavformat/bmv.c ffmpeg/libavformat/boadec.c ffmpeg/libavformat/brstm.c ffmpeg/libavformat/c93.c ffmpeg/libavformat/cache.c ffmpeg/libavformat/caf.c ffmpeg/libavformat/cafdec.c ffmpeg/libavformat/cafenc.c ffmpeg/libavformat/cavsvideodec.c ffmpeg/libavformat/cdg.c ffmpeg/libavformat/cdxl.c ffmpeg/libavformat/cinedec.c  ffmpeg/libavformat/concatdec.c ffmpeg/libavformat/crcenc.c ffmpeg/libavformat/crypto.c ffmpeg/libavformat/cutils.c ffmpeg/libavformat/dash.c ffmpeg/libavformat/dashenc.c ffmpeg/libavformat/data_uri.c ffmpeg/libavformat/dauddec.c ffmpeg/libavformat/daudenc.c ffmpeg/libavformat/dcstr.c ffmpeg/libavformat/dfa.c ffmpeg/libavformat/diracdec.c ffmpeg/libavformat/dnxhddec.c ffmpeg/libavformat/dsfdec.c ffmpeg/libavformat/dsicin.c ffmpeg/libavformat/dss.c ffmpeg/libavformat/dtsdec.c ffmpeg/libavformat/dtshddec.c ffmpeg/libavformat/dump.c ffmpeg/libavformat/dv.c ffmpeg/libavformat/dvbsub.c ffmpeg/libavformat/dvbtxt.c ffmpeg/libavformat/dvenc.c ffmpeg/libavformat/dxa.c ffmpeg/libavformat/eacdata.c ffmpeg/libavformat/electronicarts.c ffmpeg/libavformat/epafdec.c ffmpeg/libavformat/ffmdec.c ffmpeg/libavformat/ffmenc.c ffmpeg/libavformat/ffmetadec.c ffmpeg/libavformat/ffmetaenc.c ffmpeg/libavformat/file.c ffmpeg/libavformat/filmstripdec.c ffmpeg/libavformat/filmstripenc.c ffmpeg/libavformat/fitsdec.c ffmpeg/libavformat/fitsenc.c ffmpeg/libavformat/flac_picture.c ffmpeg/libavformat/flacdec.c ffmpeg/libavformat/flacenc.c ffmpeg/libavformat/flacenc_header.c ffmpeg/libavformat/flic.c ffmpeg/libavformat/flvdec.c ffmpeg/libavformat/flvenc.c ffmpeg/libavformat/format.c ffmpeg/libavformat/framecrcenc.c ffmpeg/libavformat/framehash.c ffmpeg/libavformat/frmdec.c ffmpeg/libavformat/fsb.c ffmpeg/libavformat/g722.c ffmpeg/libavformat/g723_1.c ffmpeg/libavformat/g726.c ffmpeg/libavformat/g729dec.c ffmpeg/libavformat/gdv.c ffmpeg/libavformat/genh.c ffmpeg/libavformat/gif.c ffmpeg/libavformat/gifdec.c ffmpeg/libavformat/gsmdec.c ffmpeg/libavformat/gxf.c ffmpeg/libavformat/gxfenc.c ffmpeg/libavformat/h261dec.c ffmpeg/libavformat/h263dec.c ffmpeg/libavformat/h264dec.c ffmpeg/libavformat/hashenc.c ffmpeg/libavformat/hdsenc.c ffmpeg/libavformat/hevc.c ffmpeg/libavformat/hevcdec.c ffmpeg/libavformat/hls.c ffmpeg/libavformat/hlsenc.c ffmpeg/libavformat/hlsproto.c ffmpeg/libavformat/hnm.c ffmpeg/libavformat/icodec.c ffmpeg/libavformat/icoenc.c ffmpeg/libavformat/id3v1.c ffmpeg/libavformat/id3v2.c ffmpeg/libavformat/id3v2enc.c ffmpeg/libavformat/idcin.c ffmpeg/libavformat/idroqdec.c ffmpeg/libavformat/idroqenc.c ffmpeg/libavformat/iff.c ffmpeg/libavformat/ilbc.c ffmpeg/libavformat/img2.c ffmpeg/libavformat/img2_alias_pix.c ffmpeg/libavformat/img2_brender_pix.c ffmpeg/libavformat/img2dec.c ffmpeg/libavformat/img2enc.c ffmpeg/libavformat/ingenientdec.c ffmpeg/libavformat/ipmovie.c ffmpeg/libavformat/ircam.c ffmpeg/libavformat/ircamdec.c ffmpeg/libavformat/ircamenc.c ffmpeg/libavformat/isom.c ffmpeg/libavformat/iss.c ffmpeg/libavformat/iv8.c ffmpeg/libavformat/ivfdec.c ffmpeg/libavformat/ivfenc.c ffmpeg/libavformat/jacosubdec.c ffmpeg/libavformat/jacosubenc.c ffmpeg/libavformat/jvdec.c ffmpeg/libavformat/latmenc.c ffmpeg/libavformat/lmlm4.c ffmpeg/libavformat/loasdec.c ffmpeg/libavformat/lrc.c ffmpeg/libavformat/lrcdec.c ffmpeg/libavformat/lrcenc.c ffmpeg/libavformat/lvfdec.c ffmpeg/libavformat/lxfdec.c ffmpeg/libavformat/m4vdec.c ffmpeg/libavformat/matroska.c ffmpeg/libavformat/matroskadec.c ffmpeg/libavformat/matroskaenc.c ffmpeg/libavformat/md5proto.c ffmpeg/libavformat/metadata.c ffmpeg/libavformat/mgsts.c ffmpeg/libavformat/microdvddec.c ffmpeg/libavformat/microdvdenc.c ffmpeg/libavformat/mj2kdec.c ffmpeg/libavformat/mkvtimestamp_v2.c ffmpeg/libavformat/mlpdec.c ffmpeg/libavformat/mlvdec.c ffmpeg/libavformat/mm.c ffmpeg/libavformat/mmf.c ffmpeg/libavformat/mov.c ffmpeg/libavformat/mov_chan.c ffmpeg/libavformat/movenc.c ffmpeg/libavformat/movenccenc.c ffmpeg/libavformat/movenchint.c ffmpeg/libavformat/mp3dec.c ffmpeg/libavformat/mp3enc.c ffmpeg/libavformat/mpc.c ffmpeg/libavformat/mpc8.c ffmpeg/libavformat/mpeg.c ffmpeg/libavformat/mpegenc.c ffmpeg/libavformat/mpegts.c ffmpeg/libavformat/mpegtsenc.c ffmpeg/libavformat/mpegvideodec.c ffmpeg/libavformat/mpjpeg.c ffmpeg/libavformat/mpjpegdec.c ffmpeg/libavformat/mpl2dec.c ffmpeg/libavformat/mpsubdec.c ffmpeg/libavformat/msf.c ffmpeg/libavformat/msnwc_tcp.c ffmpeg/libavformat/mtaf.c ffmpeg/libavformat/mtv.c ffmpeg/libavformat/musx.c ffmpeg/libavformat/mux.c ffmpeg/libavformat/mvdec.c ffmpeg/libavformat/mvi.c ffmpeg/libavformat/mxf.c ffmpeg/libavformat/mxfdec.c ffmpeg/libavformat/mxfenc.c ffmpeg/libavformat/mxg.c ffmpeg/libavformat/ncdec.c ffmpeg/libavformat/nistspheredec.c ffmpeg/libavformat/nsvdec.c ffmpeg/libavformat/nullenc.c ffmpeg/libavformat/nut.c ffmpeg/libavformat/nutdec.c ffmpeg/libavformat/nutenc.c ffmpeg/libavformat/nuv.c ffmpeg/libavformat/oggdec.c ffmpeg/libavformat/oggenc.c ffmpeg/libavformat/oggparsecelt.c ffmpeg/libavformat/oggparsedaala.c ffmpeg/libavformat/oggparsedirac.c ffmpeg/libavformat/oggparseflac.c ffmpeg/libavformat/oggparseogm.c ffmpeg/libavformat/oggparseopus.c ffmpeg/libavformat/oggparseskeleton.c ffmpeg/libavformat/oggparsespeex.c ffmpeg/libavformat/oggparsetheora.c ffmpeg/libavformat/oggparsevorbis.c ffmpeg/libavformat/oggparsevp8.c ffmpeg/libavformat/oma.c ffmpeg/libavformat/omadec.c ffmpeg/libavformat/omaenc.c  ffmpeg/libavformat/os_support.c ffmpeg/libavformat/paf.c ffmpeg/libavformat/pcm.c ffmpeg/libavformat/pcmdec.c ffmpeg/libavformat/pcmenc.c ffmpeg/libavformat/pjsdec.c ffmpeg/libavformat/pmpdec.c ffmpeg/libavformat/prompeg.c ffmpeg/libavformat/protocols.c ffmpeg/libavformat/psxstr.c ffmpeg/libavformat/pva.c ffmpeg/libavformat/pvfdec.c ffmpeg/libavformat/qcp.c ffmpeg/libavformat/qtpalette.c ffmpeg/libavformat/r3d.c ffmpeg/libavformat/rawdec.c ffmpeg/libavformat/rawenc.c ffmpeg/libavformat/rawutils.c ffmpeg/libavformat/rawvideodec.c ffmpeg/libavformat/realtextdec.c ffmpeg/libavformat/redspark.c ffmpeg/libavformat/replaygain.c ffmpeg/libavformat/riff.c ffmpeg/libavformat/riffdec.c ffmpeg/libavformat/riffenc.c ffmpeg/libavformat/rl2.c ffmpeg/libavformat/rm.c ffmpeg/libavformat/rmdec.c ffmpeg/libavformat/rmenc.c ffmpeg/libavformat/rmsipr.c ffmpeg/libavformat/rpl.c ffmpeg/libavformat/rsd.c ffmpeg/libavformat/rso.c ffmpeg/libavformat/rsodec.c ffmpeg/libavformat/rsoenc.c ffmpeg/libavformat/rtp.c ffmpeg/libavformat/rtpenc.c ffmpeg/libavformat/rtpenc_aac.c ffmpeg/libavformat/rtpenc_amr.c ffmpeg/libavformat/rtpenc_chain.c ffmpeg/libavformat/rtpenc_h261.c ffmpeg/libavformat/rtpenc_h263.c ffmpeg/libavformat/rtpenc_h263_rfc2190.c ffmpeg/libavformat/rtpenc_h264_hevc.c ffmpeg/libavformat/rtpenc_jpeg.c ffmpeg/libavformat/rtpenc_latm.c ffmpeg/libavformat/rtpenc_mpegts.c ffmpeg/libavformat/rtpenc_mpv.c ffmpeg/libavformat/rtpenc_vc2hq.c ffmpeg/libavformat/rtpenc_vp8.c ffmpeg/libavformat/rtpenc_vp9.c ffmpeg/libavformat/rtpenc_xiph.c ffmpeg/libavformat/s337m.c ffmpeg/libavformat/samidec.c ffmpeg/libavformat/sbgdec.c ffmpeg/libavformat/sccdec.c ffmpeg/libavformat/sccenc.c ffmpeg/libavformat/sdp.c ffmpeg/libavformat/sdr2.c ffmpeg/libavformat/sdsdec.c ffmpeg/libavformat/sdxdec.c ffmpeg/libavformat/segafilm.c ffmpeg/libavformat/segment.c ffmpeg/libavformat/shortendec.c ffmpeg/libavformat/sierravmd.c ffmpeg/libavformat/siff.c ffmpeg/libavformat/smacker.c ffmpeg/libavformat/smjpeg.c ffmpeg/libavformat/smjpegdec.c ffmpeg/libavformat/smjpegenc.c ffmpeg/libavformat/smoothstreamingenc.c ffmpeg/libavformat/smush.c ffmpeg/libavformat/sol.c ffmpeg/libavformat/soxdec.c ffmpeg/libavformat/soxenc.c ffmpeg/libavformat/spdif.c ffmpeg/libavformat/spdifdec.c ffmpeg/libavformat/spdifenc.c ffmpeg/libavformat/srtdec.c ffmpeg/libavformat/srtenc.c ffmpeg/libavformat/stldec.c ffmpeg/libavformat/subfile.c ffmpeg/libavformat/subtitles.c ffmpeg/libavformat/subviewer1dec.c ffmpeg/libavformat/subviewerdec.c ffmpeg/libavformat/supdec.c ffmpeg/libavformat/supenc.c ffmpeg/libavformat/svag.c ffmpeg/libavformat/swf.c ffmpeg/libavformat/swfdec.c ffmpeg/libavformat/swfenc.c ffmpeg/libavformat/takdec.c ffmpeg/libavformat/tedcaptionsdec.c ffmpeg/libavformat/tee.c ffmpeg/libavformat/tee_common.c ffmpeg/libavformat/teeproto.c ffmpeg/libavformat/thp.c ffmpeg/libavformat/tiertexseq.c ffmpeg/libavformat/tmv.c ffmpeg/libavformat/tta.c ffmpeg/libavformat/ttaenc.c ffmpeg/libavformat/txd.c ffmpeg/libavformat/uncodedframecrcenc.c ffmpeg/libavformat/url.c ffmpeg/libavformat/utils.c ffmpeg/libavformat/v210.c ffmpeg/libavformat/vag.c ffmpeg/libavformat/vc1dec.c ffmpeg/libavformat/vc1test.c ffmpeg/libavformat/vc1testenc.c ffmpeg/libavformat/vivo.c ffmpeg/libavformat/voc.c ffmpeg/libavformat/voc_packet.c ffmpeg/libavformat/vocdec.c ffmpeg/libavformat/vocenc.c ffmpeg/libavformat/vorbiscomment.c ffmpeg/libavformat/vpcc.c ffmpeg/libavformat/vpk.c ffmpeg/libavformat/vplayerdec.c ffmpeg/libavformat/vqf.c ffmpeg/libavformat/w64.c ffmpeg/libavformat/wavdec.c ffmpeg/libavformat/wavenc.c ffmpeg/libavformat/wc3movie.c ffmpeg/libavformat/webm_chunk.c ffmpeg/libavformat/webmdashenc.c ffmpeg/libavformat/webpenc.c ffmpeg/libavformat/webvttdec.c ffmpeg/libavformat/webvttenc.c ffmpeg/libavformat/westwood_aud.c ffmpeg/libavformat/westwood_vqa.c ffmpeg/libavformat/wsddec.c ffmpeg/libavformat/wtv_common.c ffmpeg/libavformat/wtvdec.c ffmpeg/libavformat/wtvenc.c ffmpeg/libavformat/wv.c ffmpeg/libavformat/wvdec.c ffmpeg/libavformat/wvedec.c ffmpeg/libavformat/wvenc.c ffmpeg/libavformat/xa.c ffmpeg/libavformat/xmv.c ffmpeg/libavformat/xvag.c ffmpeg/libavformat/xwma.c ffmpeg/libavformat/yop.c ffmpeg/libavformat/yuv4mpegdec.c ffmpeg/libavformat/yuv4mpegenc.c ffmpeg/libavformat/options.c
#SRC += ffmpeg/libavcodec/012v.c ffmpeg/libavcodec/4xm.c ffmpeg/libavcodec/8bps.c ffmpeg/libavcodec/8svx.c ffmpeg/libavcodec/a64multienc.c ffmpeg/libavcodec/aac_ac3_parser.c ffmpeg/libavcodec/aac_adtstoasc_bsf.c ffmpeg/libavcodec/aac_parser.c ffmpeg/libavcodec/aacadtsdec.c ffmpeg/libavcodec/aaccoder.c ffmpeg/libavcodec/aacdec.c ffmpeg/libavcodec/aacdec_fixed.c ffmpeg/libavcodec/aacenc.c ffmpeg/libavcodec/aacenc_is.c ffmpeg/libavcodec/aacenc_ltp.c ffmpeg/libavcodec/aacenc_pred.c ffmpeg/libavcodec/aacenc_tns.c ffmpeg/libavcodec/aacenctab.c ffmpeg/libavcodec/aacps_fixed.c ffmpeg/libavcodec/aacps_float.c ffmpeg/libavcodec/aacpsdsp_fixed.c ffmpeg/libavcodec/aacpsdsp_float.c ffmpeg/libavcodec/aacpsy.c ffmpeg/libavcodec/aacsbr.c ffmpeg/libavcodec/aacsbr_fixed.c ffmpeg/libavcodec/aactab.c ffmpeg/libavcodec/aandcttab.c 
#SRC += ffmpeg/libavcodec/aarch64/aacpsdsp_init_aarch64.c  ffmpeg/libavcodec/aarch64/fft_init_aarch64.c  ffmpeg/libavcodec/aarch64/fmtconvert_init.c  ffmpeg/libavcodec/aarch64/h264chroma_init_aarch64.c  ffmpeg/libavcodec/aarch64/h264dsp_init_aarch64.c ffmpeg/libavcodec/aarch64/h264dsp_neon.c ffmpeg/libavcodec/aarch64/h264idct_neon.c ffmpeg/libavcodec/aarch64/h264pred_init.c ffmpeg/libavcodec/aarch64/h264pred_neon.c ffmpeg/libavcodec/aarch64/h264qpel_init_aarch64.c ffmpeg/libavcodec/aarch64/h264qpel_neon.c ffmpeg/libavcodec/aarch64/hpeldsp_init_aarch64.c ffmpeg/libavcodec/aarch64/hpeldsp_neon.c ffmpeg/libavcodec/aarch64/idctdsp_init_aarch64.c ffmpeg/libavcodec/aarch64/mdct_neon.c ffmpeg/libavcodec/aarch64/mpegaudiodsp_init.c ffmpeg/libavcodec/aarch64/mpegaudiodsp_neon.c ffmpeg/libavcodec/aarch64/rv40dsp_init_aarch64.c ffmpeg/libavcodec/aarch64/sbrdsp_init_aarch64.c ffmpeg/libavcodec/aarch64/sbrdsp_neon.c ffmpeg/libavcodec/aarch64/simple_idct_neon.c ffmpeg/libavcodec/aarch64/synth_filter_init.c ffmpeg/libavcodec/aarch64/synth_filter_neon.c ffmpeg/libavcodec/aarch64/vc1dsp_init_aarch64.c ffmpeg/libavcodec/aarch64/videodsp.c ffmpeg/libavcodec/aarch64/videodsp_init.c ffmpeg/libavcodec/aarch64/vorbisdsp_init.c ffmpeg/libavcodec/aarch64/vorbisdsp_neon.c ffmpeg/libavcodec/aarch64/vp9dsp_init_10bpp_aarch64.c ffmpeg/libavcodec/aarch64/vp9dsp_init_12bpp_aarch64.c ffmpeg/libavcodec/aarch64/vp9dsp_init_aarch64.c ffmpeg/libavcodec/aarch64/vp9itxfm_16bpp_neon.c ffmpeg/libavcodec/aarch64/vp9itxfm_neon.c ffmpeg/libavcodec/aarch64/vp9lpf_16bpp_neon.c ffmpeg/libavcodec/aarch64/vp9lpf_neon.c ffmpeg/libavcodec/aarch64/vp9mc_16bpp_neon.c ffmpeg/libavcodec/aarch64/vp9mc_neon.c 
#SRC += ffmpeg/libavcodec/aasc.c ffmpeg/libavcodec/ac3.c ffmpeg/libavcodec/ac3_parser.c ffmpeg/libavcodec/ac3dec_data.c ffmpeg/libavcodec/ac3dec_fixed.c ffmpeg/libavcodec/ac3dec_float.c ffmpeg/libavcodec/ac3dsp.c ffmpeg/libavcodec/ac3enc.c ffmpeg/libavcodec/ac3enc_fixed.c ffmpeg/libavcodec/ac3enc_float.c ffmpeg/libavcodec/ac3tab.c ffmpeg/libavcodec/acelp_filters.c ffmpeg/libavcodec/acelp_pitch_delay.c ffmpeg/libavcodec/acelp_vectors.c ffmpeg/libavcodec/adpcm.c ffmpeg/libavcodec/adpcm_data.c ffmpeg/libavcodec/adpcmenc.c ffmpeg/libavcodec/adx.c ffmpeg/libavcodec/adx_parser.c ffmpeg/libavcodec/adxdec.c ffmpeg/libavcodec/adxenc.c ffmpeg/libavcodec/aic.c ffmpeg/libavcodec/alac.c ffmpeg/libavcodec/alac_data.c ffmpeg/libavcodec/alacdsp.c ffmpeg/libavcodec/alacenc.c ffmpeg/libavcodec/aliaspixdec.c ffmpeg/libavcodec/aliaspixenc.c ffmpeg/libavcodec/allcodecs.c ffmpeg/libavcodec/alsdec.c ffmpeg/libavcodec/amrnbdec.c ffmpeg/libavcodec/amrwbdec.c ffmpeg/libavcodec/anm.c ffmpeg/libavcodec/ansi.c ffmpeg/libavcodec/apedec.c ffmpeg/libavcodec/ass.c ffmpeg/libavcodec/ass_split.c ffmpeg/libavcodec/assdec.c ffmpeg/libavcodec/assenc.c ffmpeg/libavcodec/asv.c ffmpeg/libavcodec/asvdec.c ffmpeg/libavcodec/asvenc.c ffmpeg/libavcodec/atrac.c ffmpeg/libavcodec/atrac1.c ffmpeg/libavcodec/atrac3.c ffmpeg/libavcodec/atrac3plus.c ffmpeg/libavcodec/atrac3plusdec.c ffmpeg/libavcodec/atrac3plusdsp.c ffmpeg/libavcodec/audio_frame_queue.c ffmpeg/libavcodec/audioconvert.c ffmpeg/libavcodec/audiodsp.c ffmpeg/libavcodec/aura.c ffmpeg/libavcodec/avdct.c ffmpeg/libavcodec/avfft.c ffmpeg/libavcodec/avpacket.c ffmpeg/libavcodec/avpicture.c ffmpeg/libavcodec/avrndec.c ffmpeg/libavcodec/avs.c ffmpeg/libavcodec/avuidec.c ffmpeg/libavcodec/avuienc.c ffmpeg/libavcodec/bethsoftvideo.c ffmpeg/libavcodec/bfi.c ffmpeg/libavcodec/bgmc.c ffmpeg/libavcodec/bink.c ffmpeg/libavcodec/binkaudio.c ffmpeg/libavcodec/binkdsp.c ffmpeg/libavcodec/bintext.c ffmpeg/libavcodec/bitpacked.c ffmpeg/libavcodec/bitstream.c ffmpeg/libavcodec/bitstream_filter.c ffmpeg/libavcodec/bitstream_filters.c ffmpeg/libavcodec/blockdsp.c ffmpeg/libavcodec/bmp.c ffmpeg/libavcodec/bmp_parser.c ffmpeg/libavcodec/bmpenc.c ffmpeg/libavcodec/bmvaudio.c ffmpeg/libavcodec/bmvvideo.c ffmpeg/libavcodec/brenderpix.c ffmpeg/libavcodec/bsf.c ffmpeg/libavcodec/bswapdsp.c ffmpeg/libavcodec/c93.c ffmpeg/libavcodec/cabac.c ffmpeg/libavcodec/canopus.c ffmpeg/libavcodec/cavs.c ffmpeg/libavcodec/cavs_parser.c ffmpeg/libavcodec/cavsdata.c ffmpeg/libavcodec/cavsdec.c ffmpeg/libavcodec/cavsdsp.c ffmpeg/libavcodec/cbrt_data.c ffmpeg/libavcodec/cbrt_data_fixed.c ffmpeg/libavcodec/ccaption_dec.c ffmpeg/libavcodec/cdgraphics.c ffmpeg/libavcodec/cdxl.c ffmpeg/libavcodec/celp_filters.c ffmpeg/libavcodec/celp_math.c ffmpeg/libavcodec/cfhd.c ffmpeg/libavcodec/cfhddata.c ffmpeg/libavcodec/cga_data.c ffmpeg/libavcodec/chomp_bsf.c ffmpeg/libavcodec/cinepak.c ffmpeg/libavcodec/cinepakenc.c ffmpeg/libavcodec/clearvideo.c ffmpeg/libavcodec/cljrdec.c ffmpeg/libavcodec/cljrenc.c ffmpeg/libavcodec/cllc.c ffmpeg/libavcodec/cngdec.c ffmpeg/libavcodec/cngenc.c ffmpeg/libavcodec/codec_desc.c ffmpeg/libavcodec/cook.c ffmpeg/libavcodec/cook_parser.c ffmpeg/libavcodec/cpia.c ffmpeg/libavcodec/cscd.c ffmpeg/libavcodec/cyuv.c ffmpeg/libavcodec/d3d11va.c ffmpeg/libavcodec/dca.c ffmpeg/libavcodec/dca_core.c ffmpeg/libavcodec/dca_core_bsf.c ffmpeg/libavcodec/dca_exss.c ffmpeg/libavcodec/dca_lbr.c ffmpeg/libavcodec/dca_parser.c ffmpeg/libavcodec/dca_xll.c ffmpeg/libavcodec/dcaadpcm.c ffmpeg/libavcodec/dcadata.c ffmpeg/libavcodec/dcadct.c ffmpeg/libavcodec/dcadec.c ffmpeg/libavcodec/dcadsp.c ffmpeg/libavcodec/dcaenc.c ffmpeg/libavcodec/dcahuff.c ffmpeg/libavcodec/dct.c ffmpeg/libavcodec/dct32_fixed.c ffmpeg/libavcodec/dct32_float.c ffmpeg/libavcodec/dds.c ffmpeg/libavcodec/decode.c ffmpeg/libavcodec/dfa.c ffmpeg/libavcodec/dirac.c ffmpeg/libavcodec/dirac_arith.c ffmpeg/libavcodec/dirac_dwt.c ffmpeg/libavcodec/dirac_parser.c ffmpeg/libavcodec/dirac_vlc.c ffmpeg/libavcodec/diracdec.c ffmpeg/libavcodec/diracdsp.c ffmpeg/libavcodec/diractab.c ffmpeg/libavcodec/dnxhd_parser.c ffmpeg/libavcodec/dnxhddata.c ffmpeg/libavcodec/dnxhddec.c ffmpeg/libavcodec/dnxhdenc.c ffmpeg/libavcodec/dolby_e.c ffmpeg/libavcodec/dpcm.c ffmpeg/libavcodec/dpx.c ffmpeg/libavcodec/dpx_parser.c ffmpeg/libavcodec/dpxenc.c ffmpeg/libavcodec/dsd.c ffmpeg/libavcodec/dsddec.c ffmpeg/libavcodec/dsicinaudio.c ffmpeg/libavcodec/dsicinvideo.c ffmpeg/libavcodec/dss_sp.c ffmpeg/libavcodec/dstdec.c ffmpeg/libavcodec/dump_extradata_bsf.c ffmpeg/libavcodec/dv.c ffmpeg/libavcodec/dv_profile.c ffmpeg/libavcodec/dvaudio_parser.c ffmpeg/libavcodec/dvaudiodec.c ffmpeg/libavcodec/dvbsub.c ffmpeg/libavcodec/dvbsub_parser.c ffmpeg/libavcodec/dvbsubdec.c ffmpeg/libavcodec/dvd_nav_parser.c ffmpeg/libavcodec/dvdata.c ffmpeg/libavcodec/dvdec.c ffmpeg/libavcodec/dvdsub_parser.c ffmpeg/libavcodec/dvdsubdec.c ffmpeg/libavcodec/dvdsubenc.c ffmpeg/libavcodec/dvenc.c ffmpeg/libavcodec/dxtory.c ffmpeg/libavcodec/dxv.c ffmpeg/libavcodec/eac3_data.c ffmpeg/libavcodec/eac3enc.c ffmpeg/libavcodec/eacmv.c ffmpeg/libavcodec/eaidct.c ffmpeg/libavcodec/eamad.c ffmpeg/libavcodec/eatgq.c ffmpeg/libavcodec/eatgv.c ffmpeg/libavcodec/eatqi.c ffmpeg/libavcodec/elbg.c ffmpeg/libavcodec/encode.c ffmpeg/libavcodec/error_resilience.c ffmpeg/libavcodec/escape124.c ffmpeg/libavcodec/escape130.c ffmpeg/libavcodec/evrcdec.c ffmpeg/libavcodec/exif.c ffmpeg/libavcodec/extract_extradata_bsf.c ffmpeg/libavcodec/faandct.c ffmpeg/libavcodec/faanidct.c ffmpeg/libavcodec/faxcompr.c ffmpeg/libavcodec/fdctdsp.c ffmpeg/libavcodec/fft_fixed.c ffmpeg/libavcodec/fft_fixed_32.c ffmpeg/libavcodec/fft_float.c ffmpeg/libavcodec/fft_init_table.c ffmpeg/libavcodec/ffv1.c ffmpeg/libavcodec/ffv1dec.c ffmpeg/libavcodec/ffv1enc.c ffmpeg/libavcodec/ffwavesynth.c ffmpeg/libavcodec/fic.c ffmpeg/libavcodec/fits.c ffmpeg/libavcodec/fitsdec.c ffmpeg/libavcodec/fitsenc.c ffmpeg/libavcodec/flac.c ffmpeg/libavcodec/flac_parser.c ffmpeg/libavcodec/flacdata.c ffmpeg/libavcodec/flacdec.c ffmpeg/libavcodec/flacdsp.c ffmpeg/libavcodec/flacenc.c ffmpeg/libavcodec/flicvideo.c ffmpeg/libavcodec/flvdec.c ffmpeg/libavcodec/flvenc.c ffmpeg/libavcodec/fmtconvert.c ffmpeg/libavcodec/fmvc.c ffmpeg/libavcodec/fraps.c ffmpeg/libavcodec/frwu.c ffmpeg/libavcodec/g722.c ffmpeg/libavcodec/g722dec.c ffmpeg/libavcodec/g722dsp.c ffmpeg/libavcodec/g722enc.c ffmpeg/libavcodec/g723_1.c ffmpeg/libavcodec/g723_1dec.c ffmpeg/libavcodec/g723_1enc.c ffmpeg/libavcodec/g726.c ffmpeg/libavcodec/g729_parser.c ffmpeg/libavcodec/g729dec.c ffmpeg/libavcodec/g729postfilter.c ffmpeg/libavcodec/gdv.c ffmpeg/libavcodec/gif.c ffmpeg/libavcodec/gifdec.c ffmpeg/libavcodec/golomb.c ffmpeg/libavcodec/gsm_parser.c ffmpeg/libavcodec/gsmdec.c ffmpeg/libavcodec/gsmdec_data.c ffmpeg/libavcodec/h261.c ffmpeg/libavcodec/h261_parser.c ffmpeg/libavcodec/h261data.c ffmpeg/libavcodec/h261dec.c ffmpeg/libavcodec/h261enc.c ffmpeg/libavcodec/h263.c ffmpeg/libavcodec/h263_parser.c ffmpeg/libavcodec/h263data.c ffmpeg/libavcodec/h263dec.c ffmpeg/libavcodec/h263dsp.c ffmpeg/libavcodec/h2645_parse.c  ffmpeg/libavcodec/h264_cavlc.c ffmpeg/libavcodec/h264_direct.c ffmpeg/libavcodec/h264_loopfilter.c ffmpeg/libavcodec/h264_mb.c ffmpeg/libavcodec/h264_mp4toannexb_bsf.c  ffmpeg/libavcodec/h264dsp.c  ffmpeg/libavcodec/h264qpel.c ffmpeg/libavcodec/hap.c ffmpeg/libavcodec/hapdec.c   ffmpeg/libavcodec/hnm4video.c ffmpeg/libavcodec/hpeldsp.c ffmpeg/libavcodec/hq_hqa.c ffmpeg/libavcodec/hq_hqadata.c ffmpeg/libavcodec/hq_hqadsp.c ffmpeg/libavcodec/hqx.c ffmpeg/libavcodec/hqxdsp.c ffmpeg/libavcodec/hqxvlc.c ffmpeg/libavcodec/htmlsubtitles.c ffmpeg/libavcodec/huffman.c ffmpeg/libavcodec/huffyuv.c ffmpeg/libavcodec/huffyuvdec.c ffmpeg/libavcodec/huffyuvdsp.c ffmpeg/libavcodec/huffyuvenc.c ffmpeg/libavcodec/huffyuvencdsp.c ffmpeg/libavcodec/idcinvideo.c ffmpeg/libavcodec/idctdsp.c ffmpeg/libavcodec/iff.c ffmpeg/libavcodec/iirfilter.c ffmpeg/libavcodec/imc.c ffmpeg/libavcodec/imgconvert.c ffmpeg/libavcodec/imx_dump_header_bsf.c ffmpeg/libavcodec/indeo2.c ffmpeg/libavcodec/indeo3.c ffmpeg/libavcodec/indeo4.c ffmpeg/libavcodec/indeo5.c ffmpeg/libavcodec/intelh263dec.c ffmpeg/libavcodec/interplayacm.c ffmpeg/libavcodec/interplayvideo.c ffmpeg/libavcodec/intrax8.c ffmpeg/libavcodec/intrax8dsp.c ffmpeg/libavcodec/ituh263dec.c ffmpeg/libavcodec/ituh263enc.c ffmpeg/libavcodec/ivi.c ffmpeg/libavcodec/ivi_dsp.c ffmpeg/libavcodec/j2kenc.c ffmpeg/libavcodec/jacosubdec.c ffmpeg/libavcodec/jfdctfst.c ffmpeg/libavcodec/jfdctint.c ffmpeg/libavcodec/jni.c ffmpeg/libavcodec/jpeg2000.c ffmpeg/libavcodec/jpeg2000dec.c ffmpeg/libavcodec/jpeg2000dsp.c ffmpeg/libavcodec/jpeg2000dwt.c ffmpeg/libavcodec/jpegls.c ffmpeg/libavcodec/jpeglsdec.c ffmpeg/libavcodec/jpeglsenc.c ffmpeg/libavcodec/jpegtables.c ffmpeg/libavcodec/jrevdct.c ffmpeg/libavcodec/jvdec.c ffmpeg/libavcodec/kbdwin.c ffmpeg/libavcodec/kgv1dec.c ffmpeg/libavcodec/kmvc.c ffmpeg/libavcodec/lagarith.c ffmpeg/libavcodec/lagarithrac.c ffmpeg/libavcodec/latm_parser.c ffmpeg/libavcodec/lcldec.c ffmpeg/libavcodec/ljpegenc.c ffmpeg/libavcodec/loco.c ffmpeg/libavcodec/lossless_audiodsp.c ffmpeg/libavcodec/lossless_videodsp.c ffmpeg/libavcodec/lossless_videoencdsp.c ffmpeg/libavcodec/lpc.c ffmpeg/libavcodec/lsp.c ffmpeg/libavcodec/lzf.c ffmpeg/libavcodec/lzw.c ffmpeg/libavcodec/lzwenc.c ffmpeg/libavcodec/m101.c ffmpeg/libavcodec/mace.c ffmpeg/libavcodec/magicyuv.c ffmpeg/libavcodec/mathtables.c ffmpeg/libavcodec/mdct15.c ffmpeg/libavcodec/mdct_fixed.c ffmpeg/libavcodec/mdct_fixed_32.c ffmpeg/libavcodec/mdct_float.c ffmpeg/libavcodec/mdec.c ffmpeg/libavcodec/me_cmp.c ffmpeg/libavcodec/mediacodec.c ffmpeg/libavcodec/metasound.c ffmpeg/libavcodec/metasound_data.c ffmpeg/libavcodec/microdvddec.c ffmpeg/libavcodec/mimic.c ffmpeg/libavcodec/mjpeg2jpeg_bsf.c ffmpeg/libavcodec/mjpeg_parser.c ffmpeg/libavcodec/mjpega_dump_header_bsf.c ffmpeg/libavcodec/mjpegbdec.c ffmpeg/libavcodec/mjpegdec.c ffmpeg/libavcodec/mjpegenc.c ffmpeg/libavcodec/mjpegenc_common.c ffmpeg/libavcodec/mjpegenc_huffman.c ffmpeg/libavcodec/mlp.c ffmpeg/libavcodec/mlp_parser.c ffmpeg/libavcodec/mlpdec.c ffmpeg/libavcodec/mlpdsp.c ffmpeg/libavcodec/mlpenc.c ffmpeg/libavcodec/mlz.c ffmpeg/libavcodec/mmvideo.c ffmpeg/libavcodec/motion_est.c ffmpeg/libavcodec/motionpixels.c ffmpeg/libavcodec/movsub_bsf.c ffmpeg/libavcodec/movtextdec.c ffmpeg/libavcodec/movtextenc.c ffmpeg/libavcodec/mp3_header_decompress_bsf.c ffmpeg/libavcodec/mpc.c ffmpeg/libavcodec/mpc7.c ffmpeg/libavcodec/mpc8.c ffmpeg/libavcodec/mpeg12.c ffmpeg/libavcodec/mpeg12data.c ffmpeg/libavcodec/mpeg12dec.c ffmpeg/libavcodec/mpeg12enc.c ffmpeg/libavcodec/mpeg12framerate.c ffmpeg/libavcodec/mpeg4_unpack_bframes_bsf.c ffmpeg/libavcodec/mpeg4audio.c ffmpeg/libavcodec/mpeg4video.c ffmpeg/libavcodec/mpeg4video_parser.c ffmpeg/libavcodec/mpeg4videodec.c ffmpeg/libavcodec/mpeg4videoenc.c ffmpeg/libavcodec/mpeg_er.c ffmpeg/libavcodec/mpegaudio.c ffmpeg/libavcodec/mpegaudio_parser.c ffmpeg/libavcodec/mpegaudiodata.c ffmpeg/libavcodec/mpegaudiodec_fixed.c ffmpeg/libavcodec/mpegaudiodec_float.c ffmpeg/libavcodec/mpegaudiodecheader.c ffmpeg/libavcodec/mpegaudiodsp.c ffmpeg/libavcodec/mpegaudiodsp_data.c ffmpeg/libavcodec/mpegaudiodsp_fixed.c ffmpeg/libavcodec/mpegaudiodsp_float.c ffmpeg/libavcodec/mpegaudioenc_fixed.c ffmpeg/libavcodec/mpegaudioenc_float.c ffmpeg/libavcodec/mpegpicture.c ffmpeg/libavcodec/mpegutils.c ffmpeg/libavcodec/mpegvideo.c ffmpeg/libavcodec/mpegvideo_enc.c ffmpeg/libavcodec/mpegvideo_motion.c ffmpeg/libavcodec/mpegvideo_parser.c ffmpeg/libavcodec/mpegvideodata.c ffmpeg/libavcodec/mpegvideodsp.c ffmpeg/libavcodec/mpegvideoencdsp.c ffmpeg/libavcodec/mpl2dec.c ffmpeg/libavcodec/mqc.c ffmpeg/libavcodec/mqcdec.c ffmpeg/libavcodec/mqcenc.c ffmpeg/libavcodec/msgsmdec.c ffmpeg/libavcodec/msmpeg4.c ffmpeg/libavcodec/msmpeg4data.c ffmpeg/libavcodec/msmpeg4dec.c ffmpeg/libavcodec/msmpeg4enc.c ffmpeg/libavcodec/msrle.c ffmpeg/libavcodec/msrledec.c ffmpeg/libavcodec/mss1.c ffmpeg/libavcodec/mss12.c ffmpeg/libavcodec/mss2.c ffmpeg/libavcodec/mss2dsp.c ffmpeg/libavcodec/mss3.c ffmpeg/libavcodec/mss34dsp.c ffmpeg/libavcodec/mss4.c ffmpeg/libavcodec/msvideo1.c ffmpeg/libavcodec/msvideo1enc.c ffmpeg/libavcodec/mvcdec.c ffmpeg/libavcodec/mxpegdec.c ffmpeg/libavcodec/nellymoser.c ffmpeg/libavcodec/nellymoserdec.c ffmpeg/libavcodec/nellymoserenc.c  ffmpeg/libavcodec/noise_bsf.c ffmpeg/libavcodec/null_bsf.c ffmpeg/libavcodec/nuv.c ffmpeg/libavcodec/on2avc.c ffmpeg/libavcodec/on2avcdata.c ffmpeg/libavcodec/options.c ffmpeg/libavcodec/opus.c ffmpeg/libavcodec/opus_parser.c ffmpeg/libavcodec/opus_pvq.c ffmpeg/libavcodec/opus_rc.c ffmpeg/libavcodec/opusenc.c ffmpeg/libavcodec/opusenc_psy.c ffmpeg/libavcodec/opustab.c ffmpeg/libavcodec/pafaudio.c ffmpeg/libavcodec/pafvideo.c ffmpeg/libavcodec/pamenc.c ffmpeg/libavcodec/parser.c ffmpeg/libavcodec/pcm-bluray.c ffmpeg/libavcodec/pcm-dvd.c ffmpeg/libavcodec/pcm.c ffmpeg/libavcodec/pcx.c ffmpeg/libavcodec/pcxenc.c ffmpeg/libavcodec/pgssubdec.c ffmpeg/libavcodec/pictordec.c ffmpeg/libavcodec/pixblockdsp.c ffmpeg/libavcodec/pixlet.c ffmpeg/libavcodec/png_parser.c ffmpeg/libavcodec/pnm.c ffmpeg/libavcodec/pnm_parser.c ffmpeg/libavcodec/pnmdec.c ffmpeg/libavcodec/pnmenc.c ffmpeg/libavcodec/profiles.c ffmpeg/libavcodec/proresdata.c ffmpeg/libavcodec/proresdec2.c ffmpeg/libavcodec/proresdec_lgpl.c ffmpeg/libavcodec/proresdsp.c ffmpeg/libavcodec/proresenc_anatoliy.c ffmpeg/libavcodec/proresenc_kostya.c ffmpeg/libavcodec/psd.c ffmpeg/libavcodec/psymodel.c ffmpeg/libavcodec/ptx.c ffmpeg/libavcodec/qcelpdec.c ffmpeg/libavcodec/qdm2.c ffmpeg/libavcodec/qdmc.c ffmpeg/libavcodec/qdrw.c ffmpeg/libavcodec/qpeg.c ffmpeg/libavcodec/qpeldsp.c ffmpeg/libavcodec/qsv_api.c ffmpeg/libavcodec/qtrle.c ffmpeg/libavcodec/qtrleenc.c ffmpeg/libavcodec/r210dec.c ffmpeg/libavcodec/r210enc.c ffmpeg/libavcodec/ra144.c ffmpeg/libavcodec/ra144dec.c ffmpeg/libavcodec/ra144enc.c ffmpeg/libavcodec/ra288.c ffmpeg/libavcodec/ralf.c ffmpeg/libavcodec/rangecoder.c ffmpeg/libavcodec/ratecontrol.c ffmpeg/libavcodec/raw.c ffmpeg/libavcodec/rawdec.c ffmpeg/libavcodec/rawenc.c ffmpeg/libavcodec/rdft.c ffmpeg/libavcodec/realtextdec.c ffmpeg/libavcodec/remove_extradata_bsf.c ffmpeg/libavcodec/resample.c ffmpeg/libavcodec/resample2.c ffmpeg/libavcodec/rl.c ffmpeg/libavcodec/rl2.c ffmpeg/libavcodec/rle.c ffmpeg/libavcodec/roqaudioenc.c ffmpeg/libavcodec/roqvideo.c ffmpeg/libavcodec/roqvideodec.c ffmpeg/libavcodec/roqvideoenc.c ffmpeg/libavcodec/rpza.c ffmpeg/libavcodec/rtjpeg.c ffmpeg/libavcodec/rv10.c ffmpeg/libavcodec/rv10enc.c ffmpeg/libavcodec/rv20enc.c ffmpeg/libavcodec/rv30.c ffmpeg/libavcodec/rv30dsp.c ffmpeg/libavcodec/rv34.c ffmpeg/libavcodec/rv34_parser.c ffmpeg/libavcodec/rv34dsp.c ffmpeg/libavcodec/rv40.c ffmpeg/libavcodec/rv40dsp.c ffmpeg/libavcodec/s302m.c ffmpeg/libavcodec/s302menc.c ffmpeg/libavcodec/samidec.c ffmpeg/libavcodec/sanm.c ffmpeg/libavcodec/sbrdsp.c ffmpeg/libavcodec/sbrdsp_fixed.c ffmpeg/libavcodec/scpr.c ffmpeg/libavcodec/sgidec.c ffmpeg/libavcodec/sgienc.c ffmpeg/libavcodec/sgirledec.c ffmpeg/libavcodec/sheervideo.c ffmpeg/libavcodec/shorten.c ffmpeg/libavcodec/simple_idct.c ffmpeg/libavcodec/sinewin.c ffmpeg/libavcodec/sinewin_fixed.c ffmpeg/libavcodec/sipr.c ffmpeg/libavcodec/sipr16k.c ffmpeg/libavcodec/sipr_parser.c ffmpeg/libavcodec/smacker.c ffmpeg/libavcodec/smc.c ffmpeg/libavcodec/smvjpegdec.c ffmpeg/libavcodec/snappy.c ffmpeg/libavcodec/snow.c ffmpeg/libavcodec/snow_dwt.c ffmpeg/libavcodec/snowdec.c ffmpeg/libavcodec/snowenc.c ffmpeg/libavcodec/sonic.c ffmpeg/libavcodec/sp5xdec.c ffmpeg/libavcodec/speedhq.c ffmpeg/libavcodec/srtdec.c ffmpeg/libavcodec/srtenc.c ffmpeg/libavcodec/startcode.c ffmpeg/libavcodec/subviewerdec.c ffmpeg/libavcodec/sunrast.c ffmpeg/libavcodec/sunrastenc.c ffmpeg/libavcodec/svq1.c ffmpeg/libavcodec/svq13.c ffmpeg/libavcodec/svq1dec.c ffmpeg/libavcodec/svq1enc.c ffmpeg/libavcodec/svq3.c ffmpeg/libavcodec/synth_filter.c ffmpeg/libavcodec/tak.c ffmpeg/libavcodec/tak_parser.c ffmpeg/libavcodec/takdec.c ffmpeg/libavcodec/takdsp.c ffmpeg/libavcodec/targa.c ffmpeg/libavcodec/targa_y216dec.c ffmpeg/libavcodec/targaenc.c ffmpeg/libavcodec/textdec.c ffmpeg/libavcodec/texturedsp.c ffmpeg/libavcodec/tiertexseqv.c ffmpeg/libavcodec/tiff.c ffmpeg/libavcodec/tiff_common.c ffmpeg/libavcodec/tiff_data.c ffmpeg/libavcodec/tiffenc.c ffmpeg/libavcodec/tmv.c ffmpeg/libavcodec/tpeldsp.c ffmpeg/libavcodec/truemotion1.c ffmpeg/libavcodec/truemotion2.c ffmpeg/libavcodec/truemotion2rt.c ffmpeg/libavcodec/truespeech.c ffmpeg/libavcodec/tscc2.c ffmpeg/libavcodec/tta.c ffmpeg/libavcodec/ttadata.c ffmpeg/libavcodec/ttadsp.c ffmpeg/libavcodec/ttaenc.c ffmpeg/libavcodec/ttaencdsp.c ffmpeg/libavcodec/twinvq.c ffmpeg/libavcodec/twinvqdec.c ffmpeg/libavcodec/txd.c ffmpeg/libavcodec/ulti.c ffmpeg/libavcodec/utils.c ffmpeg/libavcodec/utvideo.c ffmpeg/libavcodec/utvideodec.c ffmpeg/libavcodec/utvideodsp.c ffmpeg/libavcodec/utvideoenc.c ffmpeg/libavcodec/v210dec.c ffmpeg/libavcodec/v210enc.c ffmpeg/libavcodec/v210x.c ffmpeg/libavcodec/v308dec.c ffmpeg/libavcodec/v308enc.c ffmpeg/libavcodec/v408dec.c ffmpeg/libavcodec/v408enc.c ffmpeg/libavcodec/v410dec.c ffmpeg/libavcodec/v410enc.c ffmpeg/libavcodec/vb.c ffmpeg/libavcodec/vble.c ffmpeg/libavcodec/vc1.c ffmpeg/libavcodec/vc1_block.c ffmpeg/libavcodec/vc1_loopfilter.c ffmpeg/libavcodec/vc1_mc.c ffmpeg/libavcodec/vc1_parser.c ffmpeg/libavcodec/vc1_pred.c ffmpeg/libavcodec/vc1data.c ffmpeg/libavcodec/vc1dec.c ffmpeg/libavcodec/vc1dsp.c ffmpeg/libavcodec/vc2enc.c ffmpeg/libavcodec/vc2enc_dwt.c ffmpeg/libavcodec/vcr1.c ffmpeg/libavcodec/videodsp.c ffmpeg/libavcodec/vima.c ffmpeg/libavcodec/vmdaudio.c ffmpeg/libavcodec/vmdvideo.c ffmpeg/libavcodec/vmnc.c ffmpeg/libavcodec/vorbis.c ffmpeg/libavcodec/vorbis_data.c ffmpeg/libavcodec/vorbis_parser.c ffmpeg/libavcodec/vorbisdec.c ffmpeg/libavcodec/vorbisdsp.c ffmpeg/libavcodec/vorbisenc.c ffmpeg/libavcodec/vp3.c ffmpeg/libavcodec/vp3_parser.c ffmpeg/libavcodec/vp3dsp.c ffmpeg/libavcodec/vp5.c ffmpeg/libavcodec/vp56.c ffmpeg/libavcodec/vp56data.c ffmpeg/libavcodec/vp56dsp.c ffmpeg/libavcodec/vp56rac.c ffmpeg/libavcodec/vp6.c ffmpeg/libavcodec/vp6dsp.c   ffmpeg/libavcodec/vqavideo.c ffmpeg/libavcodec/wavpack.c ffmpeg/libavcodec/wavpackenc.c  ffmpeg/libavcodec/webvttdec.c ffmpeg/libavcodec/webvttenc.c ffmpeg/libavcodec/wma.c ffmpeg/libavcodec/wma_common.c ffmpeg/libavcodec/wma_freqs.c ffmpeg/libavcodec/wmadec.c ffmpeg/libavcodec/wmaenc.c ffmpeg/libavcodec/wmalosslessdec.c ffmpeg/libavcodec/wmaprodec.c ffmpeg/libavcodec/wmavoice.c ffmpeg/libavcodec/wmv2.c ffmpeg/libavcodec/wmv2data.c ffmpeg/libavcodec/wmv2dec.c ffmpeg/libavcodec/wmv2dsp.c ffmpeg/libavcodec/wmv2enc.c ffmpeg/libavcodec/wnv1.c ffmpeg/libavcodec/wrapped_avframe.c ffmpeg/libavcodec/ws-snd1.c ffmpeg/libavcodec/xan.c ffmpeg/libavcodec/xbmdec.c ffmpeg/libavcodec/xbmenc.c ffmpeg/libavcodec/xface.c ffmpeg/libavcodec/xfacedec.c ffmpeg/libavcodec/xfaceenc.c ffmpeg/libavcodec/xiph.c ffmpeg/libavcodec/xl.c ffmpeg/libavcodec/xma_parser.c ffmpeg/libavcodec/xpmdec.c ffmpeg/libavcodec/xsubdec.c ffmpeg/libavcodec/xsubenc.c ffmpeg/libavcodec/xvididct.c ffmpeg/libavcodec/xwddec.c ffmpeg/libavcodec/xwdenc.c ffmpeg/libavcodec/xxan.c ffmpeg/libavcodec/y41pdec.c ffmpeg/libavcodec/y41penc.c ffmpeg/libavcodec/ylc.c ffmpeg/libavcodec/yop.c ffmpeg/libavcodec/yuv4dec.c ffmpeg/libavcodec/yuv4enc.c 
#SRC += ffmpeg/libavcodec/webp.c  ffmpeg/libavcodec/hevcdec.c ffmpeg/libavcodec/hevcdsp.c ffmpeg/libavcodec/hevcpred.c
#SRC += ffmpeg/libavutil/adler32.c ffmpeg/libavutil/aes.c ffmpeg/libavutil/aes_ctr.c ffmpeg/libavutil/audio_fifo.c ffmpeg/libavutil/avstring.c ffmpeg/libavutil/base64.c ffmpeg/libavutil/blowfish.c ffmpeg/libavutil/bprint.c ffmpeg/libavutil/camellia.c ffmpeg/libavutil/cast5.c ffmpeg/libavutil/channel_layout.c ffmpeg/libavutil/color_utils.c ffmpeg/libavutil/crc.c ffmpeg/libavutil/des.c ffmpeg/libavutil/dict.c ffmpeg/libavutil/display.c ffmpeg/libavutil/downmix_info.c ffmpeg/libavutil/error.c ffmpeg/libavutil/eval.c ffmpeg/libavutil/fifo.c ffmpeg/libavutil/file.c ffmpeg/libavutil/file_open.c ffmpeg/libavutil/fixed_dsp.c ffmpeg/libavutil/float_dsp.c ffmpeg/libavutil/frame.c ffmpeg/libavutil/hash.c ffmpeg/libavutil/hmac.c ffmpeg/libavutil/hwcontext.c ffmpeg/libavutil/imgutils.c ffmpeg/libavutil/integer.c ffmpeg/libavutil/intmath.c ffmpeg/libavutil/lfg.c ffmpeg/libavutil/lls.c ffmpeg/libavutil/log.c ffmpeg/libavutil/log2_tab.c ffmpeg/libavutil/lzo.c ffmpeg/libavutil/mastering_display_metadata.c ffmpeg/libavutil/mathematics.c ffmpeg/libavutil/md5.c ffmpeg/libavutil/mem.c ffmpeg/libavutil/murmur3.c ffmpeg/libavutil/opt.c ffmpeg/libavutil/parseutils.c ffmpeg/libavutil/pixdesc.c ffmpeg/libavutil/pixelutils.c ffmpeg/libavutil/random_seed.c ffmpeg/libavutil/rational.c ffmpeg/libavutil/rc4.c ffmpeg/libavutil/reverse.c ffmpeg/libavutil/ripemd.c ffmpeg/libavutil/samplefmt.c ffmpeg/libavutil/sha.c ffmpeg/libavutil/sha512.c ffmpeg/libavutil/spherical.c ffmpeg/libavutil/stereo3d.c ffmpeg/libavutil/tea.c ffmpeg/libavutil/threadmessage.c ffmpeg/libavutil/time.c ffmpeg/libavutil/timecode.c ffmpeg/libavutil/tree.c ffmpeg/libavutil/twofish.c ffmpeg/libavutil/utils.c ffmpeg/libavutil/xga_font_data.c ffmpeg/libavutil/xtea.c
#SRC += ffmpeg/libavutil/buffer.c ffmpeg/libavutil/slicethread.c ffmpeg/libavcodec/vp8.c ffmpeg/libavcodec/vp8_parser.c ffmpeg/libavcodec/vp8dsp.c ffmpeg/libavcodec/vp9.c ffmpeg/libavcodec/vp9_parser.c ffmpeg/libavcodec/vp9_raw_reorder_bsf.c ffmpeg/libavcodec/vp9_superframe_bsf.c ffmpeg/libavcodec/vp9_superframe_split_bsf.c ffmpeg/libavcodec/vp9block.c ffmpeg/libavcodec/vp9data.c ffmpeg/libavcodec/vp9dsp.c ffmpeg/libavcodec/vp9dsp_10bpp.c ffmpeg/libavcodec/vp9dsp_12bpp.c ffmpeg/libavcodec/vp9dsp_8bpp.c ffmpeg/libavcodec/vp9lpf.c ffmpeg/libavcodec/vp9mvs.c ffmpeg/libavcodec/vp9prob.c ffmpeg/libavcodec/vp9recon.c

#ffmpeg/libavformat/sauce.c ffmpeg/libavformat/tty.c ffmpeg/libavcodec/aarch64/aacpsdsp_neon.S ffmpeg/libavcodec/aarch64/fft_neon.S ffmpeg/libavcodec/aarch64/fmtconvert_neon.S ffmpeg/libavcodec/aarch64/h264cmc_neon.S
#ffmpeg/libavcodec/h264_cabac.c 
#ffmpeg/libavcodec/hevc_cabac.c ffmpeg/libavcodec/hevc_data.c ffmpeg/libavcodec/hevc_filter.c ffmpeg/libavcodec/hevc_mp4toannexb_bsf.c ffmpeg/libavcodec/hevc_mvs.c ffmpeg/libavcodec/hevc_parse.c ffmpeg/libavcodec/hevc_parser.c ffmpeg/libavcodec/hevc_ps.c ffmpeg/libavcodec/hevc_refs.c ffmpeg/libavcodec/hevc_sei.c
#ffmpeg/libavcodec/neon/mpegvideo.c
#ffmpeg/libavutil/aarch64/cpu.c ffmpeg/libavutil/aarch64/float_dsp_init.c ffmpeg/libavutil/aarch64/float_dsp_neon.c
#ffmpeg/libavutil/cpu.c 

OBJ := $(SRC:%.c=$(OBJDIR)/%.o)


default: libsco_ffmpeg.so


$(OBJDIR)/%.o: %.c $(DEPS) $(PASS1) $(PASS2) 
	@echo "COMPILING SOURCE $< INTO OBJECT $@"
	@mkdir -p '$(@D)'
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) -emit-llvm -S -c -o $(basename $@).ll $< $(CFLAGS)
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) -c -o $(basename $@).o $(basename $@).ll $(CFLAGS)

LD_FLAGS = 
ifdef CONFIG_SIM
LD_FLAGS += -lgcc
else
LD_FLAGS += -Wl,-error-limit=0 libcompiler_rt.a
endif


$(OBJDIR)/tramps.o: arch/$(TARGET_ARCH)/tramps.S
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) $(CFLAGS) -c -o $(OBJDIR)/tramps.o arch/$(TARGET_ARCH)/tramps.S

libsco_ffmpeg.so: $(OBJ)
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) $(CFLAGS) -o $@ -nostdlib -Wl,-eouter_c -fPIE -fPIC $(OBJ) $(LD_FLAGS)

clean:
	rm -rf ./*.o ./*.so ./*.ll ./1.txt $(OBJDIR)

