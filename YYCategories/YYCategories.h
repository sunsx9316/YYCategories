//
//  YYCategories.h
//  YYCategories <https://github.com/ibireme/YYCategories>
//
//  Created by ibireme on 13/3/29.
//  Copyright (c) 2015 ibireme.
//
//  This source code is licensed under the MIT-style license found in the
//  LICENSE file in the root directory of this source tree.
//

#import <Foundation/Foundation.h>

FOUNDATION_EXPORT double YYCategoriesVersionNumber;
FOUNDATION_EXPORT const unsigned char YYCategoriesVersionString[];

#import "YYCategoriesMacro.h"
#import "NSObject+YYAdd.h"
#import "NSObject+YYAddForKVO.h"
#import "NSObject+YYAddForARC.h"
#import "NSData+YYAdd.h"
#import "NSString+YYAdd.h"
#import "NSArray+YYAdd.h"
#import "NSDictionary+YYAdd.h"
#import "NSDate+YYAdd.h"
#import "NSNumber+YYAdd.h"
#import "NSNotificationCenter+YYAdd.h"
#import "NSKeyedUnarchiver+YYAdd.h"
#import "NSTimer+YYAdd.h"
#import "NSBundle+YYAdd.h"
#import "NSThread+YYAdd.h"
#import "YYColor+YYAdd.h"
#import "CALayer+YYAdd.h"
#import "YYCGUtilities.h"

#if TARGET_OS_IPHONE
#import "UIImage+YYAdd.h"
#import "UIControl+YYAdd.h"
#if !TARGET_OS_TV
#import "UIBarButtonItem+YYAdd.h"
#endif
#import "UIGestureRecognizer+YYAdd.h"
#import "UIView+YYAdd.h"
#import "UIScrollView+YYAdd.h"
#import "UITableView+YYAdd.h"
#import "UITextField+YYAdd.h"
#import "UIScreen+YYAdd.h"
#import "UIDevice+YYAdd.h"
#import "UIApplication+YYAdd.h"
#import "UIFont+YYAdd.h"
#import "UIBezierPath+YYAdd.h"
#endif

