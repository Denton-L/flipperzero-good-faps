#pragma once

enum NfcBlankCardScannerEvent {
    NfcBlankCardScannerEventTypeDetected,
    NfcBlankCardScannerEventTypeDetectedInvalid, // TODO
    NfcBlankCardScannerEventTypeNotDetected,
};

typedef void (*NfcBlankCardScannerCallback)(void* context, enum NfcBlankCardScannerEvent event);

struct NfcBlankCardScanner;

struct NfcBlankCardScanner* nfc_blank_card_scanner_alloc(void);
void nfc_blank_card_scanner_free(struct NfcBlankCardScanner* instance);
void nfc_blank_card_scanner_start(struct NfcBlankCardScanner* instance, NfcBlankCardScannerCallback callback, void* context);
void nfc_blank_card_scanner_stop(struct NfcBlankCardScanner* instance);
