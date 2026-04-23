# Polygon Ninja (C++ Physics Engine)

Polygon Ninja is a 2D physics engine game inspired by Fruit Ninja, built from scratch in C++ using WinAPI and GDI+. This project focuses heavily on custom math, physics mechanics, and rendering optimizations.


![PolygonNinja](https://github.com/user-attachments/assets/f8a2ec5c-fc45-4d96-ba4e-53cb61a478be)

## Core Mechanics & Mathematics

### Slicing Logic
The slicing mechanic relies on evaluating a continuous history of mouse movements rather than a single raycast.

**Algorithm (The "Out-In-Out" Rule):**
1. **Input Tracking:** The mouse position is recorded every frame in `g_swordPoints` to generate a continuous cutting trail.
2. **Intersection Check:** The engine evaluates the sword's history iteratively.
3. **Entry/Exit Detection:** It identifies an entry point (where the trail transitions from outside to inside the polygon) and an exit point (where the trail transitions back outside).
4. **Clipping:** The **Sutherland-Hodgman algorithm** (`ClipShape`) geometrically slices the original polygon's vertex list into two distinct new lists, representing the cut fragments.

**Mathematical Implementations:**
* **Point-in-Polygon Test:** Verifies intersections using custom logic (`KVectorUtil::IsPointInPolygon`).
* **Line Segment Intersection:** Calculates the exact contact points for slicing (`LineSegmentsIntersect`).
* **Convex Hull Generation:** Ensures all newly sliced fragments form mathematically valid, stable physics bodies.

### Collision Optimization (Spatial Hashing)
As polygons are continuously sliced into smaller fragments, a naive O(N²) collision detection approach causes severe performance drops. To solve this, **Spatial Hashing (Broad Phase)** was implemented.

* **Grid System:** The game world is partitioned into cells of a fixed size (`m_cellSize`).
* **Hashing:** A specialized hash function maps 2D grid coordinates (x, y) into a 1D bucket index.
* **Insertion:** Every frame, physical bodies are assigned to buckets based on their Axis-Aligned Bounding Box (AABB).
* **Retrieval:** Fine-grained collision checks are only performed between bodies occupying the same bucket.
* **Impact:** Drastically reduces collision complexity, approaching O(N) in sparse environments.
* **Key File:** `KSpatialHash.h`

### Rendering Optimization (GDI+)
Standard Windows GDI+ drawing is inherently slow if GDI objects (like Pens and Brushes) are repeatedly created and destroyed every draw call.

* **Pen Caching:** Implemented within `KVectorUtil::DrawLine`. Static variables retain the last used Pen, and a new Pen is created *only* if the color, width, or style changes.
* **Particle Batching:** Implemented within `KParticleSystem::Draw`. Rather than drawing lines (which involves matrix math for every individual segment), particles are batched and drawn as simple GDI Rectangle calls. It leverages `DC_BRUSH` to change colors rapidly without needing object reallocation.
