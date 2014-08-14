//
//  BRWalletManager.h
//  BreadWallet
//
//  Created by Aaron Voisine on 3/2/14.
//  Copyright (c) 2014 Aaron Voisine <voisine@gmail.com>
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.

#import <Foundation/Foundation.h>

#define BRWalletManagerSeedChangedNotification @"BRWalletManagerSeedChangedNotification"

@class BRWallet, BRTransaction;

@interface BRWalletManager : NSObject<UIAlertViewDelegate>

@property (nonatomic, readonly) BRWallet *wallet;
@property (nonatomic, strong) NSData *seed;
@property (nonatomic, strong) NSString *seedPhrase;
@property (nonatomic, readonly) NSTimeInterval seedCreationTime; // interval since refrence date, 00:00:00 01/01/01 GMT
@property (nonatomic, strong) NSNumberFormatter *format;

+ (instancetype)sharedInstance;
-(NSString*)randomSeed;
- (void)generateRandomSeed;

// given a private key, queries blockchain for unspent outputs and calls the completion block with a signed transaction
// that will sweep the balance into wallet (doesn't publish the tx)
- (void)sweepPrivateKey:(NSString *)privKey withFee:(BOOL)fee
completion:(void (^)(BRTransaction *tx, NSError *error))completion;
-(int64_t)amountForDouble:(double)amount;
- (int64_t)amountForDouble:(double)amount withMaximumFractionDigits:(int)maximumDigits;
- (int64_t)amountForString:(NSString *)string;
- (int64_t)amountForString:(NSString *)string withMaximumFractionDigits:(int)maximumDigits;
- (NSString *)stringForAmount:(int64_t)amount;
- (NSString *)localCurrencyStringForAmount:(int64_t)amount;

-(NSDictionary*)currencyExchangeRates;
-(void)setLocalCurrency:(NSString*)currencyCode withData:(NSDictionary*)exchangeData;
-(NSString*)currencyCode;
-(NSDictionary*)localCurrencyData;

@end
