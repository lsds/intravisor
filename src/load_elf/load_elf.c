/*
 * The code in this file largely originates from the userlandexec code available
 * at https://github.com/bediger4000/userlandexec. The following license and
 * copyright applies.
 * 
 * BSD 3-Clause License
 * 
 * Copyright (c) 2017, Bruce Ediger
 * Copyright 2016, 2017, 2018 Imperial College London
 * 
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 * 
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * 
 * * Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <elf.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

#include <load_elf.h>

#define ROUNDUP(x, y)   ((((x)+((y)-1))/(y))*(y))
#define ALIGNDOWN(k, v) ((unsigned long)(k)&(~((unsigned long)(v)-1)))

static void *memcopy(void *dest, const void *src, unsigned long n);
static void *map_file(char *file_to_map, struct stat* sb);
static int copy_in(char *filename, void *address);

#ifdef __linux__ 
#define SHM_ANON "test"
#define SHM_ANON2 "test2"
#endif

void load_elf(char* file_to_map, void *base_addr, encl_map_info* result) {
    char *mapped;
    struct stat sb;
    Elf64_Ehdr *hdr;
    Elf64_Phdr *pdr;
    int i, anywhere;
    void *text_segment = 0, *segment_base = 0;
    void *entry_point = 0;
    unsigned long initial_vaddr = 0, load_segments_size;
    unsigned int mapflags = MAP_PRIVATE;

    /* TODO Do not copy the whole file into memory instead of doing a
     * file-backed mmap? */
    mapped = map_file(file_to_map, &sb);

    if(mapped < 0) {
        result->base = (void *)-1;
        return;
    }

    int fd = open(file_to_map, O_RDONLY, 0);

    hdr = (Elf64_Ehdr *)mapped;
    pdr = (Elf64_Phdr *)((unsigned long)hdr + hdr->e_phoff);

       Elf64_Shdr *sections = (Elf64_Shdr *)((char *)mapped + hdr->e_shoff);
       Elf64_Sym *symtab = NULL;



       for (i = 0; i < hdr->e_shnum; i++) {
//				printf("type = %x %x %d\n", sections[i].sh_type, SHT_SYMTAB, sections[i].sh_name);

				Elf64_Shdr *shdr = (mapped + hdr->e_shoff);
				int shnum = hdr->e_shnum;

				Elf64_Shdr *sh_strtab = &shdr[hdr->e_shstrndx];
				const char *const sh_strtab_p = mapped + sh_strtab->sh_offset;

//				printf("type: %d, name = %s\n", sections[i].sh_type, sh_strtab_p + sections[i].sh_name);

				if(strncmp("__cap_relocs", sh_strtab_p + sections[i].sh_name, strlen("__cap_relocs")) == NULL) {
					if(result->cap_relocs) {
						printf("something is wrong, cap_relocs copied already\n");
					}
					result->cap_relocs = malloc(sections[i].sh_size);
					if(result->cap_relocs == NULL) {
						printf("cannot allocate memory for cap_relocs\n");
						break;
					}
					memcpy(result->cap_relocs, mapped + sections[i].sh_offset, sections[i].sh_size);
					result->cap_relocs_size = sections[i].sh_size;
			  }


               if (sections[i].sh_type == SHT_SYMTAB) {
          				Elf64_Sym *symtab = (Elf64_Sym *)(mapped + sections[i].sh_offset);
  //        			void *symtab_end = (Elf64_Sym *)((char *)symtab + shdr[i].sh_size);
						char *strtab = (char *)(mapped + sections[sections[i].sh_link].sh_offset);

//						printf("map = %p, symtab = %p, strtab = %p %d\n", mapped, symtab, strtab,  sections[i].sh_size/sizeof(Elf64_Sym));

						for(int j =0; j < sections[i].sh_size/sizeof(Elf64_Sym); j++) {
								Elf64_Sym *ts = (Elf64_Sym *)&symtab[j];
								if(strcmp("ret_from_monitor", &strtab[ts->st_name]) == 0) {
//								printf("%ld: %ld %ld %ld %ld %lx %ld\n", j,ts->st_name, ts->st_info, ts->st_other, ts->st_shndx, ts->st_value, ts->st_size);
//									printf("string = %s, val=%lx\n", &strtab[ts->st_name], ts->st_value);
									result->ret_point = ts->st_value;
//									break;
								}

								if(strcmp("syscall_handler", &strtab[ts->st_name]) == 0) {
//								printf("%ld: %ld %ld %ld %ld %lx %ld\n", j,ts->st_name, ts->st_info, ts->st_other, ts->st_shndx, ts->st_value, ts->st_size);
//									printf("string = %s, val=%lx\n", &strtab[ts->st_name], ts->st_value);
									result->syscall_handler = ts->st_value;
//									break;
								}


						}

               }
       }



    for (i = 0; i < hdr->e_phnum; ++i) {
        if (pdr[i].p_type == PT_LOAD) {
            if (!anywhere && pdr[i].p_vaddr == 0) {
                anywhere = 1;  /* map it anywhere, like ld.so, or PIC code. */
            } else if (!anywhere && !segment_base) {
                segment_base = (void*) pdr[i].p_vaddr;
            }

            // Determine total in-memory size of all loadable sections:
            // Virtual address/Offset plus memory size of last loadable segment.
            load_segments_size = (unsigned long) ((void*) pdr[i].p_vaddr - segment_base) + pdr[i].p_memsz;
        }
    }

    if (!anywhere)
        mapflags |= MAP_FIXED;

    entry_point = (void *)hdr->e_entry;

    for (i = 0; i < hdr->e_phnum; ++i, ++pdr)
    {
        unsigned int protflags = PROT_EXEC;
        unsigned long map_addr = 0, map_len;
        unsigned long unaligned_map_addr = 0;
        off_t offset;
        void *segment;

        if (pdr->p_type != PT_LOAD)  /* Segment not "loadable" */
            continue;

        if (text_segment != 0 && anywhere) {
            unaligned_map_addr
                = (unsigned long)text_segment
                + ((unsigned long)pdr->p_vaddr - (unsigned long)initial_vaddr)
                ;
            map_addr = ALIGNDOWN((unsigned long)unaligned_map_addr, 0x1000);
            mapflags |= MAP_FIXED;
        } else if (!anywhere) {
            map_addr = ALIGNDOWN(pdr->p_vaddr, 0x1000);
        } else {
            map_addr = ROUNDUP((unsigned long) base_addr, 0x1000);
            if (map_addr)
                mapflags |= MAP_FIXED;
        }

        if (!anywhere && initial_vaddr == 0)
            initial_vaddr = pdr->p_vaddr;

        // If this is the first allocation, mmap memory for all segments to
        // ensure that later MAP_FIXED mmap calls for subsequent segments do
        // not overlap with unrelated previously mapped regions.
        if (!text_segment) {
            map_len = ROUNDUP(load_segments_size, 0x1000);
        } else {
            map_len = ROUNDUP(pdr->p_vaddr + pdr->p_memsz, 0x1000) - ALIGNDOWN(pdr->p_vaddr, 0x1000);
        }

        offset = ALIGNDOWN(pdr->p_offset, 0x1000);
        protflags = (((pdr->p_flags&PF_R) ? PROT_READ : 0) |
            ((pdr->p_flags&PF_W) ? PROT_WRITE: 0) |
            ((pdr->p_flags&PF_X) ? PROT_EXEC : 0) );
//               if(map_addr >= 0x20533000ll)
//                         protflags |= PROT_WRITE;


//todo: we use statically allocated heap in LKL, and memory should be writable and executable because it is used to load the binary. needs to be changed
//        if (pdr->p_flags & PF_W)
#if 0
	        segment = mmap((void *)map_addr, map_len, protflags | PROT_WRITE | PROT_EXEC, MAP_SHARED | MAP_FIXED , sfd, offset);
#else
	        segment = mmap((void *)map_addr, map_len, protflags | PROT_WRITE | PROT_EXEC, MAP_PRIVATE|MAP_FIXED, fd, offset);
#endif
//		else
//	        segment = mmap((void *)map_addr, map_len, protflags|PROT_EXEC, mapflags , fd, offset);

        if (segment == (void *) -1) {
            result->base = (void *)-1;
            fprintf(stderr, "1. Could not map segment (%p) of %s: %s\n", (void*)pdr->p_vaddr, file_to_map, strerror(errno));
			while(1);
        } else 
			printf("Mapped %p, segment = %p, map_aaadr = %p, map_len = %lx\n", (void*)pdr->p_vaddr, segment, map_addr, map_len);

        if (pdr->p_memsz > pdr->p_filesz) {
            size_t brk = (size_t)segment + pdr->p_filesz;
            size_t pgbrk = ROUNDUP(brk, 0x1000);
#if 0
//why alighned down? if brk is not paged aligned, then alighdonw corrupts memory
          memset((void *)brk, 0, pgbrk - ALIGNDOWN(brk, 0x1000));
#else
          memset((void *)brk, 0, pgbrk - brk);
#endif
///
			size_t len2 = (size_t)segment + map_len - pgbrk;
			void *mmap_ret1 = mmap((void *)pgbrk             , (size_t)segment + map_len - pgbrk, protflags|PROT_EXEC, MAP_ANON|MAP_PRIVATE|MAP_FIXED, -1, 0);

            if ((pgbrk - (size_t)segment) < map_len && (mmap_ret1 == MAP_FAILED)) {
                result->base = (void *)-1;
                fprintf(stderr, "Could not map segment 1 (%p) of %s: %s\n", (void*)pdr->p_vaddr, file_to_map, strerror(errno));
				while(1);
            } else
		printf("SHARED MAPPING %p--%p\n", mmap_ret1, mmap_ret1+(size_t)segment + map_len - pgbrk);

        }

        if (!text_segment)
        {
            text_segment = segment;
            initial_vaddr = pdr->p_vaddr;
#if 0
            if (anywhere) {
                entry_point = (void *)((unsigned long)entry_point
                        - (unsigned long)pdr->p_vaddr
                        + (unsigned long)text_segment);
				}
#endif
        }
    }

    close(fd);

    result->base = text_segment;
    result->size = load_segments_size;
    result->entry_point = entry_point;

done:
    munmap(mapped, sb.st_size);
}

void *memcopy(void *dest, const void *src, unsigned long n) {
    unsigned long i;
    unsigned char *d = (unsigned char *)dest;
    unsigned char *s = (unsigned char *)src;

    for (i = 0; i < n; ++i)
        d[i] = s[i];

    return dest;
}

void *map_file(char *file_to_map, struct stat* sb) {
    void *mapped;

    if (stat(file_to_map, sb) < 0)
    {
        return (void *)-1;
    }

    mapped = mmap(0, sb->st_size, PROT_READ|PROT_WRITE|PROT_EXEC, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
    if (mapped == (void *)-1)
    {
		perror("mmap");
        return (void *)-1;
    }

    copy_in(file_to_map, mapped);

    return mapped;
}

int copy_in(char *filename, void *address) {
    int fd, cc;
    off_t offset = 0;
    char buf[1024];

    if (0 > (fd = open(filename, 0, 0)))
    {
        return -1;
    }

    while (0 < (cc = read(fd, buf, sizeof(buf))))
    {
        memcpy((void*) ((uintptr_t) address + offset), buf, cc);
        offset += cc;
    }

    close(fd);

    return 0;
}
