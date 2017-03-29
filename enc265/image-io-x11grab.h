/*
 * H.265 video codec.
 * Copyright (c) 2013-2014 struktur AG, Dirk Farin <farin@struktur.de>
 *
 * Authors: struktur AG, Dirk Farin <farin@struktur.de>
 *
 * This file is part of libde265.
 *
 * libde265 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * libde265 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with libde265.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef IMAGE_IO_X11GRAB_H
#define IMAGE_IO_X11GRAB_H

#include "libde265/image-io.h"
#include "libde265/acceleration.h"

#include <X11/Xlib.h>
#include <X11/extensions/XShm.h>


class ImageSource_X11Grab : public ImageSource
{
 public:
  LIBDE265_API ImageSource_X11Grab();
  virtual LIBDE265_API ~ImageSource_X11Grab();

  void setAccelerationFunctions(const acceleration_functions& func) { mAcceleration = func; }

  void setTargetColorspace(enum de265_chroma chroma,
                           enum de265_colorspace colorspace)
  {
    mTargetChroma = chroma;
    mTargetColorspace = colorspace;
  }

  void LIBDE265_API set_position(int x,int y) { mX=x; mY=y; }
  void LIBDE265_API set_size(int w,int h) { mWidth=w; mHeight=h; }

  //virtual ImageStatus  get_status();
  virtual LIBDE265_API image* get_image(bool block=true);
  virtual LIBDE265_API void skip_frames(int n) { }

  virtual LIBDE265_API int get_width() const { return mWidth; }
  virtual LIBDE265_API int get_height() const { return mHeight; }

 private:
  int mX, mY;
  int mWidth,mHeight;

  bool mInitialized;
  bool mUseShm;
  Display* mDisplay;
  XImage* mImage;
  XShmSegmentInfo mShminfo;

  acceleration_functions mAcceleration;

  enum de265_chroma     mTargetChroma     = de265_chroma_420;
  enum de265_colorspace mTargetColorspace = de265_colorspace_YCbCr;

  bool init();
};

#endif
