/*
 * Copyright 2016 Bruno Ribeiro
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef HQX_HQ2X_HH
#define HQX_HQ2X_HH

#include <stdint.h>

class HQ2x
{
	public:
		HQ2x();

		~HQ2x();

		static uint32_t ARGBtoAYUV(
			uint32_t value );

		static bool isDifferent(
			uint32_t yuv1,
			uint32_t yuv2,
			uint32_t trY,
			uint32_t trU,
			uint32_t trV,
			uint32_t trA );

		uint32_t *resize(
			const uint32_t *image,
			uint32_t width,
			uint32_t height,
			uint32_t *output,
			uint32_t trY = 0x30,
			uint32_t trU = 0x07,
			uint32_t trV = 0x06,
			uint32_t trA = 0x50,
			bool wrapX = false,
			bool wrapY = false ) const;
};


#endif  // HQX_HQ2X_HH
