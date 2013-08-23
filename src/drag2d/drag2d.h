/*
* Copyright (c) 2012-2013 Guang Zhu http://runnersoft.net
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

#ifndef _WX_GUI_H_
#define _WX_GUI_H_

#include "algorithms/DelaunayTriangulation.h"

#include "dataset/Bitmap.h"
#include "dataset/Image.h"
#include "dataset/RawPixels.h"
#include "dataset/ISymbol.h"
#include "dataset/SymbolFactory.h"
#include "dataset/SymbolMgr.h"
#include "dataset/ImageSymbol.h"
#include "dataset/ShapeSymbol.h"
#include "dataset/EShapeSymbol.h"
#include "dataset/MeshSymbol.h"
#include "dataset/CombinationSymbol.h"
#include "dataset/ComplexSymbol.h"
#include "dataset/AnimSymbol.h"
#include "dataset/Patch9Symbol.h"
#include "dataset/ISprite.h"
#include "dataset/SpriteFactory.h"
#include "dataset/ImageSprite.h"
#include "dataset/ShapeSprite.h"
#include "dataset/EShapeSprite.h"
#include "dataset/MeshSprite.h"
#include "dataset/CombinationSprite.h"
#include "dataset/ComplexSprite.h"
#include "dataset/Patch9Sprite.h"
#include "dataset/AnimSprite.h"
#include "dataset/TextSprite.h"
#include "dataset/ChainShape.h"
#include "dataset/CosineShape.h"
#include "dataset/PolygonShape.h"
#include "dataset/RectShape.h"
#include "dataset/CircleShape.h"
#include "dataset/BezierShape.h"
#include "dataset/PolygonBody.h"
#include "dataset/CircleBody.h"
#include "dataset/ChainBody.h"
#include "dataset/BodyData.h"
#include "dataset/BodyFactory.h"
#include "dataset/JointDef.h"
#include "dataset/Joint.h"
#include "dataset/Layer.h"
#include "dataset/BVFactory.h"

#include "view/GLCanvas.h"
#include "view/Camera.h"
#include "view/LibraryPanel.h"
#include "view/ILibraryPage.h"
#include "view/LibraryList.h"
#include "view/LibraryImagePage.h"
#include "view/LibraryShapePage.h"
#include "view/LibraryEShapePage.h"
#include "view/LibraryMeshPage.h"
#include "view/LibraryCombinationPage.h"
#include "view/LibraryComplexPage.h"
#include "view/LibraryAnimPage.h"
#include "view/Library9PatchPage.h"
#include "view/PropertySettingPanel.h"
#include "view/IPropertySetting.h"
#include "view/SpritePropertySetting.h"
#include "view/MultiSpritesPropertySetting.h"
#include "view/TextPropertySetting.h"
#include "view/SymbolPropertySetting.h"
#include "view/DialogStageCanvas.h"
#include "view/SpriteStageCanvas.h"
#include "view/ShapeStageCanvas.h"
#include "view/ShapesPanelImpl.h"
#include "view/SpritesPanelImpl.h"
#include "view/MultiShapesImpl.h"
#include "view/MultiSpritesImpl.h"
#include "view/PhysicsPanelImpl.h"
#include "view/ToolbarPanel.h"

#include "operator/AbstractEditOP.h"
#include "operator/NullEditOP.h"
#include "operator/ZoomViewOP.h"
#include "operator/ArrangeSpriteOP.h"
#include "operator/ArrangeSpriteFixOP.h"
#include "operator/DragPhysicsOP.h"
#include "operator/UniversalArrangeOP.h"
#include "operator/SelectSpritesOP.h"
#include "operator/SelectPixelsOP.h"
#include "operator/SelectShapesOP.h"
#include "operator/DrawRectangleOP.h"
#include "operator/DrawPolylineOP.h"
#include "operator/DrawPolygonEdgeOP.h"
#include "operator/DrawCurveOP.h"
#include "operator/PasteSymbolOP.h"
#include "operator/PasteSymbolRandomOP.h"
#include "operator/PasteSymbolCaptureOP.h"
#include "operator/PasteSymbolTileOP.h"
#include "operator/PasteSymbolPhysicsOP.h"
#include "operator/PasteSymbolPhysicsRandomOP.h"
#include "operator/PasteSpriteOP.h"
#include "operator/DrawPencilLineOP.h"
#include "operator/DrawPenLineOP.h"
#include "operator/DrawCosineCurveOP.h"
#include "operator/EditPolylineOP.h"
#include "operator/EditPolylinesOP.h"
#include "operator/EditRectOP.h"
#include "operator/EditCircleOP.h"
#include "operator/EditBezierOP.h"

#include "history/AbstractAtomicOP.h"

#include "component/AbstractEditCMPT.h"
#include "component/UniversalCMPT.h"
#include "component/PasteSymbolScaleCMPT.h"
#include "component/PasteSymbolRandomCMPT.h"
#include "component/PasteSymbolOffsetCMPT.h"
#include "component/PasteSymbolPhysicsCMPT.h"
#include "component/PasteSpriteCMPT.h"
#include "component/DrawPencilLineCMPT.h"
#include "component/DrawLineCMPT.h"
#include "component/DrawPolygonCMPT.h"
#include "component/NodeCaptureCMPT.h"
#include "component/EditNodesCMPT.h"
#include "component/EditPolylinesCMPT.h"
#include "component/EditPolygonCMPT.h"
#include "component/LayersMgrCMPT.h"
#include "component/MousePositionCMPT.h"
#include "component/UniversalArrangeCMPT.h"

#include "widgets/SetValueDialog.h"
#include "widgets/ListItem.h"
#include "widgets/VerticalImageList.h"
#include "widgets/DragTargetNull.h"
#include "widgets/SelectDrawTypeWidget.h"
#include "widgets/LayersMgrWidget.h"
#include "widgets/PasteSymbolRandomWidget.h"

#include "common/LibJpeg.h"
#include "common/log.h"
#include "common/FileNameParser.h"
#include "common/FilenameTools.h"
#include "common/PolylineFileAdapter.h"
#include "common/CircleFileAdapter.h"
#include "common/CombinationFileAdapter.h"
#include "common/MeshFileAdapter.h"
#include "common/ShapeFileAdapter.h"
#include "common/TexPackerAdapter.h"
#include "common/TexturePackerFileAdapter.h"
#include "common/Settings.h"
#include "common/Math.h"
#include "common/visitors.h"
#include "common/tools.h"
#include "common/Random.h"
#include "common/Context.h"

#include "render/b2Render.h"
#include "render/PrimitiveDraw.h"
#include "render/DrawSelectedShapeVisitor.h"
#include "render/DrawShapesVisitor.h"
#include "render/DrawSelectedSpriteVisitor.h"
#include "render/DrawSpritesVisitor.h"
#include "render/SpriteDraw.h"
#include "render/SpriteBatch.h"

#endif // _WX_GUI_H_
