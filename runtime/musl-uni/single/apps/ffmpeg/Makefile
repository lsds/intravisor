MAKEFILE := $(shell git rev-parse --show-toplevel)/cfg.mak
include $(MAKEFILE)

LIBOS_PATH := ../..

CFLAGS=-fPIC -fPIE -pie -g -O2  -nostdinc \
	$(TARGET_FLAGS_LINUX) $(SYSROOT_FLAGS_PURE) -B$(CROSS_COMPILE) $(ARCH_PURE) \
	 -I $(LIBOS_PATH)/musl-host/include  -I.\
	-I ffmpeg -DHAVE_AV_CONFIG_H

DEPS = 
OBJDIR = obj
SRC = main.c

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



OBJ := $(SRC:%.c=$(OBJDIR)/%.o)


default: libffmpeg.so


$(OBJDIR)/%.o: %.c $(DEPS) $(PASS1) $(PASS2) 
	@echo "COMPILING SOURCE $< INTO OBJECT $@"
	@mkdir -p '$(@D)'
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) -emit-llvm -S -c -o $(basename $@).ll $< $(CFLAGS)
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) -c -o $(basename $@).o $(basename $@).ll $(CFLAGS)


libffmpeg.so: $(OBJ)
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) $(CFLAGS) -o $@ -nostdlib -Wl,-eouter_c -fPIE -fPIC $(OBJ) $(LD_FLAGS) $(LIBOS_PATH)/libmusl-uni.a

clean:
	rm -rf ./*.o ./*.so ./*.ll ./1.txt $(OBJDIR)

install:
	sudo mkdir -p ${INSTALL_PATH}
	sudo cp ./*.yaml ./*.so ./*.ci ${INSTALL_PATH}
