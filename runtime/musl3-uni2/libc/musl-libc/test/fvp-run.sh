#!/bin/bash

if [[ ! -v FVP_MODEL_PATH ]]; then
    echo "FVP_MODEL_PATH must be set" 1>&2
    exit 1
fi

if [[ ! -v FVP_IMAGE_PATH ]]; then
    echo "FVP_IMAGE_PATH must be set" 1>&2
    exit 1
fi

if [[ ! -v FVP_FIRMWARE_PATH ]]; then
    echo "FVP_FIRMWARE_PATH must be set" 1>&2
    exit 1
fi

if [[ ! -v FVP_SHARED_DIR ]]; then
    echo "FVP_SHARED_DIR must be set" 1>&2
    exit 1
fi

mkdir -p ${FVP_SHARED_DIR}

tmp="$(mktemp -d)"
trap "rm -rf ${tmp}" EXIT
mkfifo ${tmp}/port

${FVP_MODEL_PATH} \
    --data Morello_Top.css.scp.armcortexm7ct=${FVP_FIRMWARE_PATH}/scp_romfw.bin@0x0 \
    --data Morello_Top.css.mcp.armcortexm7ct=${FVP_FIRMWARE_PATH}/mcp_romfw.bin@0x0 \
    -C "Morello_Top.soc.scp_qspi_loader.fname=${FVP_FIRMWARE_PATH}/scp_fw.bin" \
    -C "Morello_Top.soc.mcp_qspi_loader.fname=${FVP_FIRMWARE_PATH}/mcp_fw.bin" \
    -C "css.scp.armcortexm7ct.INITVTOR=0x0" \
    -C "css.mcp.armcortexm7ct.INITVTOR=0x0" \
    -C "css.trustedBootROMloader.fname=${FVP_FIRMWARE_PATH}/tf-bl1.bin" \
    -C "board.ap_qspi_loader.fname=${FVP_FIRMWARE_PATH}/fip.bin" \
    -C "board.virtioblockdevice.image_path=${FVP_IMAGE_PATH}" \
    -C "css.pl011_uart_ap.out_file=/dev/null" \
    -C "css.scp.pl011_uart_scp.out_file=/dev/null" \
    -C "css.mcp.pl011_uart0_mcp.out_file=/dev/null" \
    -C "css.pl011_uart_ap.unbuffered_output=1" \
    -C "displayController=1" \
    -C "board.virtio_rng.enabled=1" \
    -C "board.virtio_rng.seed=0" \
    -C "board.virtio_net.enabled=1" \
    -C "board.virtio_net.hostbridge.userNetworking=1" \
    -C "board.virtio_net.transport=legacy" \
    -C "board.virtio_net.hostbridge.userNetPorts=5555=5555" \
    -C "board.virtio_p9.root_path=${FVP_SHARED_DIR}" \
    -C "disable_visualisation=true" \
    -C "board.terminal_uart0_board.start_telnet=0" \
    -C "board.terminal_uart1_board.start_telnet=0" \
    -C "css.mcp.terminal_uart0.start_telnet=0" \
    -C "css.mcp.terminal_uart1.start_telnet=0" \
    -C "css.scp.terminal_uart_aon.start_telnet=0" \
    -C "css.terminal_sec_uart_ap.start_telnet=0" \
    -C "css.terminal_uart1_ap.start_telnet=0" \
    -C "css.terminal_uart_ap.start_telnet=1" \
    -C "css.terminal_uart_ap.terminal_command=echo %port > ${tmp}/port" &
read port < ${tmp}/port
echo ${port} > fvp.port
