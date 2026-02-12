#pragma once
#include <furi.h>
#include <stdlib.h>
#include <string.h>
#include <lib/subghz/protocols/base.h>
#include <lib/subghz/types.h>
#include <lib/subghz/blocks/const.h>
#include <lib/subghz/blocks/decoder.h>
#include <lib/subghz/blocks/encoder.h>
#include <lib/subghz/blocks/generic.h>
#include <flipper_format/flipper_format.h>

#include "../defines.h"

#define FIAT_PROTOCOL_V0_NAME "Fiat V0"

/* Worst-case encoder upload capacity (LevelDuration entries)
 * Per burst:
 * - preamble: FIAT_V0_PREAMBLE_PAIRS * 2
 * - data: max 141 entries (see encoder differential rules)
 * Between bursts: one inter-burst gap entry
 */
#define FIAT_V0_DATA_MAX_EDGES  ((63 + 6) * 2 + 3)
#define FIAT_V0_BURST_MAX_EDGES (FIAT_V0_PREAMBLE_PAIRS * 2 + FIAT_V0_DATA_MAX_EDGES)
#define FIAT_V0_UPLOAD_CAP \
    (FIAT_V0_TOTAL_BURSTS * FIAT_V0_BURST_MAX_EDGES + (FIAT_V0_TOTAL_BURSTS - 1))
#define FIAT_V0_GAP_US 800

typedef struct SubGhzProtocolDecoderFiatV0 SubGhzProtocolDecoderFiatV0;
typedef struct SubGhzProtocolEncoderFiatV0 SubGhzProtocolEncoderFiatV0;

extern const SubGhzProtocol fiat_protocol_v0;

// Decoder functions
void* subghz_protocol_decoder_fiat_v0_alloc(SubGhzEnvironment* environment);
void subghz_protocol_decoder_fiat_v0_free(void* context);
void subghz_protocol_decoder_fiat_v0_reset(void* context);
void subghz_protocol_decoder_fiat_v0_feed(void* context, bool level, uint32_t duration);
uint8_t subghz_protocol_decoder_fiat_v0_get_hash_data(void* context);
SubGhzProtocolStatus subghz_protocol_decoder_fiat_v0_serialize(
    void* context,
    FlipperFormat* flipper_format,
    SubGhzRadioPreset* preset);
SubGhzProtocolStatus
    subghz_protocol_decoder_fiat_v0_deserialize(void* context, FlipperFormat* flipper_format);
void subghz_protocol_decoder_fiat_v0_get_string(void* context, FuriString* output);

// Encoder functions
void* subghz_protocol_encoder_fiat_v0_alloc(SubGhzEnvironment* environment);
void subghz_protocol_encoder_fiat_v0_free(void* context);
SubGhzProtocolStatus
    subghz_protocol_encoder_fiat_v0_deserialize(void* context, FlipperFormat* flipper_format);
void subghz_protocol_encoder_fiat_v0_stop(void* context);
LevelDuration subghz_protocol_encoder_fiat_v0_yield(void* context);
