#pragma once

struct NfcBlankCardScanner;

struct NfcBlankCardScanner* nfc_blank_card_scanner_alloc(void);
void nfc_blank_card_scanner_free(struct NfcBlankCardScanner* instance);
