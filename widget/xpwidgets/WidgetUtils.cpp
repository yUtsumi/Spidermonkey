/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 * vim: sw=2 ts=8 et :
 */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "mozilla/WidgetUtils.h"

namespace mozilla {

gfx::Matrix
ComputeTransformForRotation(const nsIntRect& aBounds,
                              ScreenRotation aRotation)
{
    gfx::Matrix transform;
    static const gfx::Float floatPi = static_cast<gfx::Float>(M_PI);

    switch (aRotation) {
    case ROTATION_0:
        break;
    case ROTATION_90:
        transform.Translate(aBounds.width, 0);
        transform = gfx::Matrix::Rotation(floatPi / 2) * transform;
        break;
    case ROTATION_180:
        transform.Translate(aBounds.width, aBounds.height);
        transform = gfx::Matrix::Rotation(floatPi) * transform;
        break;
    case ROTATION_270:
        transform.Translate(0, aBounds.height);
        transform = gfx::Matrix::Rotation(floatPi * 3 / 2) * transform;
        break;
    default:
        MOZ_CRASH("Unknown rotation");
    }
    return transform;
}

gfx::Matrix
ComputeTransformForUnRotation(const nsIntRect& aBounds,
                              ScreenRotation aRotation)
{
    gfx::Matrix transform;
    static const gfx::Float floatPi = static_cast<gfx::Float>(M_PI);

    switch (aRotation) {
    case ROTATION_0:
        break;
    case ROTATION_90:
        transform.Translate(0, aBounds.height);
        transform = gfx::Matrix::Rotation(floatPi * 3 / 2) * transform;
        break;
    case ROTATION_180:
        transform.Translate(aBounds.width, aBounds.height);
        transform = gfx::Matrix::Rotation(floatPi) * transform;
        break;
    case ROTATION_270:
        transform.Translate(aBounds.width, 0);
        transform = gfx::Matrix::Rotation(floatPi / 2) * transform;
        break;
    default:
        MOZ_CRASH("Unknown rotation");
    }
    return transform;
}

nsIntRect RotateRect(nsIntRect aRect,
                     const nsIntRect& aBounds,
                     ScreenRotation aRotation)
{
  switch (aRotation) {
    case ROTATION_0:
      return aRect;
    case ROTATION_90:
      return nsIntRect(aRect.y,
                       aBounds.width - aRect.x - aRect.width,
                       aRect.height, aRect.width);
    case ROTATION_180:
      return nsIntRect(aBounds.width - aRect.x - aRect.width,
                       aBounds.height - aRect.y - aRect.height,
                       aRect.width, aRect.height);
    case ROTATION_270:
      return nsIntRect(aBounds.height - aRect.y - aRect.height,
                       aRect.x,
                       aRect.height, aRect.width);
    default:
      MOZ_CRASH("Unknown rotation");
      return aRect;
  }
}
} // namespace mozilla
