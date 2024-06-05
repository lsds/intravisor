MAKEFILE := $(shell git rev-parse --show-toplevel)/cfg.mak
include $(MAKEFILE)

PROG=app14
OBJDIR = obj

CROSS_LIBC_PATH=../../libc/build/
CFLAGS= -I../../libc/build/include -DINTRAVISOR -O2

CFLAGS+= -I. -I libsodium/src/libsodium/include/ -I libsodium/src/libsodium/include/sodium/ -I libsodium/test/quirks/ -D BENCHMARKS
CFLAGS+= -DPACKAGE_NAME=\"libsodium\" -DPACKAGE_TARNAME=\"libsodium\" -DPACKAGE_VERSION=\"1.0.19\" -DPACKAGE_STRING=\"libsodium\ 1.0.19\" -DPACKAGE_BUGREPORT=\"https://github.com/jedisct1/libsodium/issues\" -DPACKAGE_URL=\"https://libsodium.org\" -DPACKAGE=\"libsodium\" -DVERSION=\"1.0.19\" -DHAVE_STDIO_H=1 -DHAVE_STDLIB_H=1 -DHAVE_STRING_H=1 -DHAVE_INTTYPES_H=1 -DHAVE_STDINT_H=1 -DHAVE_STRINGS_H=1 -DHAVE_UNISTD_H=1 -D_GNU_SOURCE=1 -DNATIVE_LITTLE_ENDIAN=1 -DHAVE_ALLOCA_H=1 -DHAVE_ALLOCA=1 -DHAVE_GETPID=1 -DHAVE_POSIX_MEMALIGN=1 -DHAVE_NANOSLEEP=1 -DHAVE_CLOCK_GETTIME=1 -DCONFIGURED=1 -D__STDC_NO_THREADS__=1

SRC += main.c 
SRC += libsodium/src/libsodium/crypto_aead/aegis128l/aead_aegis128l.c
SRC += libsodium/src/libsodium/crypto_aead/aegis128l/aegis128l_soft.c
SRC += libsodium/src/libsodium/crypto_aead/aegis256/aead_aegis256.c
SRC += libsodium/src/libsodium/crypto_aead/aegis256/aegis256_soft.c
SRC += libsodium/src/libsodium/crypto_aead/aes256gcm/aead_aes256gcm.c
SRC += libsodium/src/libsodium/crypto_aead/chacha20poly1305/aead_chacha20poly1305.c
SRC += libsodium/src/libsodium/crypto_aead/xchacha20poly1305/aead_xchacha20poly1305.c
SRC += libsodium/src/libsodium/crypto_auth/crypto_auth.c
SRC += libsodium/src/libsodium/crypto_auth/hmacsha256/auth_hmacsha256.c
SRC += libsodium/src/libsodium/crypto_auth/hmacsha512/auth_hmacsha512.c
SRC += libsodium/src/libsodium/crypto_auth/hmacsha512256/auth_hmacsha512256.c
SRC += libsodium/src/libsodium/crypto_box/crypto_box.c
SRC += libsodium/src/libsodium/crypto_box/crypto_box_easy.c
SRC += libsodium/src/libsodium/crypto_box/crypto_box_seal.c
SRC += libsodium/src/libsodium/crypto_box/curve25519xsalsa20poly1305/box_curve25519xsalsa20poly1305.c
SRC += libsodium/src/libsodium/crypto_core/ed25519/ref10/ed25519_ref10.c
SRC += libsodium/src/libsodium/crypto_core/hchacha20/core_hchacha20.c
SRC += libsodium/src/libsodium/crypto_core/hsalsa20/ref2/core_hsalsa20_ref2.c
SRC += libsodium/src/libsodium/crypto_core/hsalsa20/core_hsalsa20.c
SRC += libsodium/src/libsodium/crypto_core/salsa/ref/core_salsa_ref.c
SRC += libsodium/src/libsodium/crypto_core/softaes/softaes.c
SRC += libsodium/src/libsodium/crypto_generichash/crypto_generichash.c
SRC += libsodium/src/libsodium/crypto_generichash/blake2b/generichash_blake2.c
SRC += libsodium/src/libsodium/crypto_generichash/blake2b/ref/blake2b-compress-ref.c
SRC += libsodium/src/libsodium/crypto_generichash/blake2b/ref/blake2b-ref.c
SRC += libsodium/src/libsodium/crypto_generichash/blake2b/ref/generichash_blake2b.c
SRC += libsodium/src/libsodium/crypto_hash/crypto_hash.c
SRC += libsodium/src/libsodium/crypto_hash/sha256/hash_sha256.c
SRC += libsodium/src/libsodium/crypto_hash/sha256/cp/hash_sha256_cp.c
SRC += libsodium/src/libsodium/crypto_hash/sha512/hash_sha512.c
SRC += libsodium/src/libsodium/crypto_hash/sha512/cp/hash_sha512_cp.c
SRC += libsodium/src/libsodium/crypto_kdf/blake2b/kdf_blake2b.c
SRC += libsodium/src/libsodium/crypto_kdf/crypto_kdf.c
SRC += libsodium/src/libsodium/crypto_kdf/hkdf/kdf_hkdf_sha256.c
SRC += libsodium/src/libsodium/crypto_kdf/hkdf/kdf_hkdf_sha512.c
SRC += libsodium/src/libsodium/crypto_kx/crypto_kx.c
SRC += libsodium/src/libsodium/crypto_onetimeauth/crypto_onetimeauth.c
SRC += libsodium/src/libsodium/crypto_onetimeauth/poly1305/onetimeauth_poly1305.c
SRC += libsodium/src/libsodium/crypto_onetimeauth/poly1305/donna/poly1305_donna.c
SRC += libsodium/src/libsodium/crypto_pwhash/argon2/argon2-core.c
SRC += libsodium/src/libsodium/crypto_pwhash/argon2/argon2-encoding.c
SRC += libsodium/src/libsodium/crypto_pwhash/argon2/argon2-fill-block-ref.c
SRC += libsodium/src/libsodium/crypto_pwhash/argon2/argon2.c
SRC += libsodium/src/libsodium/crypto_pwhash/argon2/blake2b-long.c
SRC += libsodium/src/libsodium/crypto_pwhash/argon2/pwhash_argon2i.c
SRC += libsodium/src/libsodium/crypto_pwhash/argon2/pwhash_argon2id.c
SRC += libsodium/src/libsodium/crypto_pwhash/crypto_pwhash.c
SRC += libsodium/src/libsodium/crypto_scalarmult/crypto_scalarmult.c
SRC += libsodium/src/libsodium/crypto_scalarmult/curve25519/ref10/x25519_ref10.c
SRC += libsodium/src/libsodium/crypto_scalarmult/curve25519/scalarmult_curve25519.c
SRC += libsodium/src/libsodium/crypto_secretbox/crypto_secretbox.c
SRC += libsodium/src/libsodium/crypto_secretbox/crypto_secretbox_easy.c
SRC += libsodium/src/libsodium/crypto_secretbox/xsalsa20poly1305/secretbox_xsalsa20poly1305.c
SRC += libsodium/src/libsodium/crypto_secretstream/xchacha20poly1305/secretstream_xchacha20poly1305.c
SRC += libsodium/src/libsodium/crypto_shorthash/crypto_shorthash.c
SRC += libsodium/src/libsodium/crypto_shorthash/siphash24/shorthash_siphash24.c
SRC += libsodium/src/libsodium/crypto_shorthash/siphash24/ref/shorthash_siphash24_ref.c
SRC += libsodium/src/libsodium/crypto_sign/crypto_sign.c
SRC += libsodium/src/libsodium/crypto_sign/ed25519/sign_ed25519.c
SRC += libsodium/src/libsodium/crypto_sign/ed25519/ref10/keypair.c
SRC += libsodium/src/libsodium/crypto_sign/ed25519/ref10/open.c
SRC += libsodium/src/libsodium/crypto_sign/ed25519/ref10/sign.c
SRC += libsodium/src/libsodium/crypto_stream/chacha20/stream_chacha20.c
SRC += libsodium/src/libsodium/crypto_stream/chacha20/ref/chacha20_ref.c
SRC += libsodium/src/libsodium/crypto_stream/crypto_stream.c
SRC += libsodium/src/libsodium/crypto_stream/salsa20/stream_salsa20.c
SRC += libsodium/src/libsodium/crypto_stream/xsalsa20/stream_xsalsa20.c
SRC += libsodium/src/libsodium/crypto_verify/verify.c
SRC += libsodium/src/libsodium/randombytes/randombytes.c
SRC += libsodium/src/libsodium/sodium/codecs.c
SRC += libsodium/src/libsodium/sodium/core.c
SRC += libsodium/src/libsodium/sodium/runtime.c
SRC += libsodium/src/libsodium/sodium/utils.c
SRC += libsodium/src/libsodium/sodium/version.c

SRC += libsodium/src/libsodium/crypto_stream/salsa20/ref/salsa20_ref.c
SRC += libsodium/src/libsodium/randombytes/sysrandom/randombytes_sysrandom.c

##
SRC += libsodium/src/libsodium/crypto_box/curve25519xchacha20poly1305/box_curve25519xchacha20poly1305.c
SRC += libsodium/src/libsodium/crypto_box/curve25519xchacha20poly1305/box_seal_curve25519xchacha20poly1305.c
SRC += libsodium/src/libsodium/crypto_core/ed25519/core_ed25519.c
SRC += libsodium/src/libsodium/crypto_core/ed25519/core_ristretto255.c
SRC += libsodium/src/libsodium/crypto_pwhash/scryptsalsa208sha256/crypto_scrypt-common.c
SRC += libsodium/src/libsodium/crypto_pwhash/scryptsalsa208sha256/scrypt_platform.c
SRC += libsodium/src/libsodium/crypto_pwhash/scryptsalsa208sha256/pbkdf2-sha256.c
SRC += libsodium/src/libsodium/crypto_pwhash/scryptsalsa208sha256/pwhash_scryptsalsa208sha256.c
SRC += libsodium/src/libsodium/crypto_pwhash/scryptsalsa208sha256/nosse/pwhash_scryptsalsa208sha256_nosse.c
SRC += libsodium/src/libsodium/crypto_scalarmult/ed25519/ref10/scalarmult_ed25519_ref10.c
SRC += libsodium/src/libsodium/crypto_scalarmult/ristretto255/ref10/scalarmult_ristretto255_ref10.c
SRC += libsodium/src/libsodium/crypto_secretbox/xchacha20poly1305/secretbox_xchacha20poly1305.c
SRC += libsodium/src/libsodium/crypto_shorthash/siphash24/shorthash_siphashx24.c
SRC += libsodium/src/libsodium/crypto_shorthash/siphash24/ref/shorthash_siphashx24_ref.c
SRC += libsodium/src/libsodium/crypto_sign/ed25519/ref10/obsolete.c
SRC += libsodium/src/libsodium/crypto_stream/salsa2012/ref/stream_salsa2012_ref.c
SRC += libsodium/src/libsodium/crypto_stream/salsa2012/stream_salsa2012.c
SRC += libsodium/src/libsodium/crypto_stream/salsa208/ref/stream_salsa208_ref.c
SRC += libsodium/src/libsodium/crypto_stream/salsa208/stream_salsa208.c
SRC += libsodium/src/libsodium/crypto_stream/xchacha20/stream_xchacha20.c

SRC += libsodium/src/libsodium/randombytes/internal/randombytes_internal_random.c

SRC += libsodium/test/default/secretbox_easy.c 

OBJ := $(SRC:%.c=$(OBJDIR)/%.o)

ROOTFS := root.cpio

all: $(ROOTFS)


$(OBJDIR)/%.o: %.c
	@echo "COMPILING SOURCE $< INTO OBJECT $@"
	@mkdir -p '$(@D)'
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) -emit-llvm -S -c -o $(basename $@).ll $< $(CFLAGS)
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) -c -o $(basename $@).o $(basename $@).ll $(CFLAGS)

$(PROG): $(OBJ)
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) -nostdlib -nostartfiles -o $@ $(OBJ) $(CROSS_LIBC_PATH)/lib/crt1.o $(CROSS_LIBC_PATH)/lib/crti.o $(CROSS_LIBC_PATH)/lib/crtn.o \
	-L$(CROSS_LIBC_PATH)/lib -Wl,-dynamic-linker=/lib/ld-linux-aarch64_purecap.so.1 ../../libc/libcompiler_rt.a -lc -pie

clean:
	rm -rf $(ROOTFS) $(PROG) *.o ./$(OBJDIR) rootfs/app1

install:
	sudo mkdir -p ${INSTALL_PATH}
	sudo cp ./*.yaml ./*.ci ./libldso.so ${INSTALL_PATH}
	sudo cp $(ROOTFS) ${INSTALL_PATH}/$(ROOTFS)_$(shell basename $(shell ls *.yaml) .yaml)

$(ROOTFS): $(PROG) $(CROSS_LIBC_PATH)/lib/libc.so
	cp $(PROG) rootfs/app1
	cp $(CROSS_LIBC_PATH)/lib/libc.so ./libldso.so
	cd rootfs && find . -print -depth | sort | $(CPIO) -vo -H newc > ../$(ROOTFS)
