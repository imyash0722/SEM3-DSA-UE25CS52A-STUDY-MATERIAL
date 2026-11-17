document.addEventListener('DOMContentLoaded', function() {
  if (typeof mermaid !== 'undefined') {
    // Use default theme - we handle dark/light via CSS variables
    mermaid.initialize({
      startOnLoad: true,
      theme: 'default',
      securityLevel: 'loose',
      flowchart: {
        useMaxWidth: true,
        htmlLabels: true,
        curve: 'basis'
      },
      sequence: {
        useMaxWidth: true
      }
    });
  }
});

// Re-render Mermaid diagrams when navigating (for SPA-like behavior)
if (typeof mermaid !== 'undefined') {
  document.addEventListener('DOMContentLoaded', function() {
    mermaid.init(undefined, document.querySelectorAll('.mermaid'));
  });
}